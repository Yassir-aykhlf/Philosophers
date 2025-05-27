# Philosophers - Dining Philosophers Problem

A high-performance, thread-safe implementation of the classic Dining Philosophers synchronization problem using POSIX threads in C. This solution demonstrates advanced concurrent programming techniques, precise timing mechanisms, and robust resource management.

## Problem Overview

The Dining Philosophers problem illustrates fundamental challenges in concurrent programming: resource sharing, deadlock prevention, and synchronization. Five (or N) philosophers sit around a table with forks between them, alternating between thinking, eating, and sleeping. Each philosopher needs two forks to eat, creating potential for deadlock and starvation.

## Architecture & Design

### Core Components

- **Simulation Engine**: Central coordinator managing the entire dining session
- **Philosopher Threads**: Individual threads representing each philosopher's lifecycle  
- **Monitor Thread**: Dedicated watchdog for death detection and completion monitoring
- **Resource Management**: Thread-safe fork allocation with deadlock prevention
- **Precision Timing**: Microsecond-accurate sleep implementation for realistic simulation

### Thread Safety Strategy

```c
typedef struct s_simulation {
    pthread_mutex_t *forks;        // Per-fork mutexes
    pthread_mutex_t print_mutex;   // Synchronized output
    pthread_mutex_t sim_mutex;     // Simulation state protection
    // ... other fields
} t_simulation;
```

The implementation employs multiple mutex layers:
- **Fork mutexes**: Prevent simultaneous fork access
- **Meal mutexes**: Protect individual philosopher meal tracking
- **Print mutex**: Ensure atomic output operations
- **Simulation mutex**: Guard global simulation state

### Deadlock Prevention

The solution implements **resource ordering** to prevent circular wait conditions:

```c
// Philosophers acquire forks in consistent order (lower ID first)
if (philo->left_fork < philo->right_fork) {
    first_fork = philo->left_fork;
    second_fork = philo->right_fork;
} else {
    first_fork = philo->right_fork;
    second_fork = philo->left_fork;
}
```

This approach ensures no circular dependency chains can form, mathematically guaranteeing deadlock-free execution.

## Key Features

### High-Precision Timing
Custom `precise_usleep()` implementation provides microsecond accuracy:
- Hybrid approach: `usleep()` for coarse delays, busy-waiting for precision
- Prevents timing drift in long simulations
- Optimized for both performance and accuracy

### Intelligent Philosopher Scheduling
- **Even-numbered philosophers**: Start with 1ms delay to reduce contention
- **Odd philosopher count**: Dynamic thinking time calculation prevents starvation
- **Optimized fork acquisition**: Minimizes blocking time

### Death Detection
The monitor thread continuously checks philosopher health:
- Non-blocking health checks using separate meal mutexes
- Atomic simulation termination on death detection
- Race condition prevention in death reporting

### Memory Management
- Comprehensive resource cleanup on all exit paths
- Proper mutex destruction sequence
- Exception-safe initialization with rollback on failure

## Usage

```bash
# Compile
make

# Clean build (recommended after structure changes)
make clean && make

# Debug build with debug symbols
make debug

# See all available build targets
make help

# Run simulation
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: meals_required]

# Examples
./philo 5 800 200 200        # 5 philosophers, basic simulation
./philo 4 410 200 200        # Edge case: should not die
./philo 5 800 200 200 7      # Stop after 7 meals per philosopher
```

### Parameters
- `num_philosophers`: Number of philosophers (1-200)
- `time_to_die`: Maximum time between meals (ms)
- `time_to_eat`: Duration of eating (ms)  
- `time_to_sleep`: Duration of sleeping (ms)
- `meals_required`: Optional meal limit per philosopher

## Implementation Details

### Thread Lifecycle
Each philosopher follows this state machine:
1. **Think**: Calculate optimal thinking duration
2. **Acquire Forks**: Use ordered acquisition to prevent deadlock
3. **Eat**: Update meal tracking atomically
4. **Sleep**: Rest for specified duration
5. **Repeat** until death or meal completion

### Special Cases Handled
- **Single Philosopher**: Cannot eat (only one fork available)
- **Even Philosopher Count**: Staggered start prevents initial contention
- **Odd Philosopher Count**: Dynamic thinking time prevents starvation
- **Race Conditions**: All shared state access is mutex-protected

### Performance Optimizations
- Minimal mutex hold times
- Efficient monitor polling (100μs intervals)
- Lock-free simulation state checks where possible
- Optimized fork acquisition ordering

## Testing Scenarios

The implementation handles various edge cases:

```bash
# No deaths should occur
./philo 4 410 200 200
./philo 5 800 200 200

# Tight timing (deaths may occur)
./philo 4 310 200 100

# Large scale
./philo 100 800 200 200

# Meal completion
./philo 5 800 200 200 5
```

## Project Structure

```
philosophers/
├── include/              # Header files
│   └── philo.h          # Type definitions and function prototypes
├── src/                 # Source code organized by functionality
│   ├── core/            # Core application logic
│   │   ├── philo.c      # Main entry point and initialization
│   │   ├── init.c       # Simulation and philosopher initialization
│   │   ├── threads.c    # Thread creation and management
│   │   └── routine.c    # Main philosopher routine logic
│   ├── actions/         # Philosopher actions and fork management
│   │   ├── actions.c    # Philosopher actions (eat, sleep, think)
│   │   ├── actions_utils.c # Action utility functions
│   │   └── forks.c      # Fork (mutex) management
│   ├── monitor/         # Simulation monitoring
│   │   ├── monitor.c    # Death detection and simulation monitoring
│   │   └── monitor_utils.c # Monitoring utility functions
│   └── utils/           # General utilities
│       ├── utils.c      # General utilities and argument parsing
│       ├── getters.c    # Timestamp and time management
│       ├── log_utils.c  # Thread-safe logging functions
│       ├── sim_utils.c  # Simulation utility functions
│       ├── timing.c     # Precision timing utilities
│       └── special_cases.c # Edge case handling
├── obj/                 # Object files (mirrors src structure)
├── docs/                # Documentation
│   └── PROJECT_STRUCTURE.md # Detailed project organization guide
├── build/               # Build artifacts
├── Makefile            # Enhanced build configuration
└── README.md           # This file
```

## Technical Specifications

- **Language**: C (C99 standard)
- **Threading**: POSIX Threads (pthread)
- **Compiler**: GCC with `-Wall -Wextra -Werror` flags
- **Platform**: Unix-like systems (Linux, macOS)
- **Memory Management**: Manual allocation with comprehensive cleanup
- **Synchronization**: Mutex-based with deadlock prevention
- **Build System**: Enhanced Makefile with organized object file structure
- **Project Organization**: Modular structure with separated concerns

### Build Features

- **Organized Build**: Object files stored in `obj/` directory mirroring source structure
- **Automatic Dependencies**: Header dependency tracking
- **Debug Support**: `make debug` for development builds
- **Clean Separation**: Source and build artifacts kept separate
- **Help System**: `make help` shows available targets

## Thread Safety Guarantees

- **Data Race Freedom**: All shared data access is mutex-protected
- **Deadlock Freedom**: Resource ordering prevents circular waits
- **Livelock Prevention**: Randomized delays and intelligent scheduling
- **Starvation Resistance**: Fair resource allocation algorithms

## Performance Characteristics

- **Scalability**: Tested up to 200 philosophers
- **Latency**: Sub-millisecond response to death conditions
- **Memory Usage**: O(n) space complexity
- **CPU Efficiency**: Minimal busy-waiting, optimized mutex usage

## Advanced Features

### Adaptive Thinking Time
For odd philosopher counts, thinking time is dynamically calculated:
```c
think_time = (time_to_eat * 2) - time_to_sleep;
```
This prevents starvation in asymmetric scenarios.

### Graceful Degradation
The system handles resource exhaustion gracefully:
- Failed thread creation triggers cleanup
- Memory allocation failures are handled safely
- Partial initialization states are properly cleaned up

## Learning Outcomes

This implementation demonstrates mastery of:
- **Concurrent Programming**: Thread synchronization and communication
- **Deadlock Prevention**: Resource ordering and careful lock management
- **System Programming**: POSIX APIs and low-level timing
- **Software Architecture**: Modular design and separation of concerns
- **Performance Optimization**: Efficient algorithms and data structures
- **Project Organization**: Professional C project structure and build systems

### Code Organization Benefits

The structured layout provides:
- **Maintainability**: Related functionality grouped in logical modules
- **Scalability**: Easy addition of new features without cluttering
- **Clarity**: Clear separation between core logic, actions, monitoring, and utilities
- **Professional Standards**: Follows industry conventions for C projects
- **Build Efficiency**: Organized object files and dependency management
