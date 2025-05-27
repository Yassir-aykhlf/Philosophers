# Philosophers

A high-quality implementation of the classic dining philosophers problem in C, demonstrating advanced concurrent programming concepts and best practices.

## Features

- **Thread-safe implementation** with proper mutex usage
- **Deadlock prevention** using ordered resource allocation
- **Precise timing** with custom sleep function for better accuracy
- **Race condition protection** throughout the codebase
- **Memory leak prevention** with proper cleanup
- **Robust error handling** for all system calls
- **Optimized performance** with minimal resource usage

## Architecture

### Core Components

- `philo.c` - Main entry point and initialization
- `actions.c` - Philosopher actions (eat, sleep, think)
- `monitor.c` - Death detection and simulation monitoring
- `threads.c` - Thread management and lifecycle
- `timing.c` - Precise timing utilities
- `resources.c` - Fork/mutex management
- `utils.c` - Input validation and utility functions

### Thread Safety Features

1. **Ordered fork acquisition** prevents circular wait deadlocks
2. **Atomic state checks** prevent race conditions
3. **Protected shared resources** with appropriate mutexes
4. **Safe simulation termination** without data races

### Performance Optimizations

1. **Precise microsleep** implementation for accurate timing
2. **Thinking time calculation** to prevent busy waiting
3. **Optimized monitor intervals** for responsive death detection
4. **Thread staggering** to reduce initial contention

## Usage

```bash
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: num_meals]
```

### Examples

```bash
# Basic test with 4 philosophers
./philo 4 410 200 200

# Test with meal limit
./philo 5 800 200 200 7

# Stress test
./philo 200 410 200 200
```

## Code Quality Improvements Made

### Critical Bug Fixes
- Fixed race conditions in simulation state checks
- Corrected timestamp calculation for millisecond precision
- Fixed return values in utility functions
- Added proper integer overflow protection

### Thread Safety Enhancements
- Implemented atomic access to shared variables
- Added proper mutex ordering to prevent deadlocks
- Protected all critical sections appropriately
- Fixed data races in monitoring logic

### Performance Improvements
- Replaced `usleep()` with precise timing function
- Added intelligent thinking time calculation
- Optimized monitor checking frequency
- Reduced unnecessary system calls

### Memory Management
- Added comprehensive cleanup for all mutexes
- Fixed potential memory leaks in error conditions
- Proper resource deallocation ordering

### Error Handling
- Enhanced input validation with range checking
- Added proper error propagation
- Improved thread creation failure handling
- Better error messages for debugging

### Code Organization
- Centralized status printing to reduce code duplication
- Improved function naming and consistency
- Better separation of concerns
- Enhanced readability and maintainability

## Technical Details

### Deadlock Prevention
Uses the "ordered resource allocation" strategy where philosophers always pick up the lower-numbered fork first, preventing circular wait conditions.

### Timing Precision
Custom `precise_usleep()` function combines `usleep()` with active waiting for sub-millisecond accuracy, crucial for passing strict timing tests.

### Death Detection
Monitor thread runs with high frequency (100μs intervals) to detect philosopher deaths as quickly as possible while minimizing CPU usage.

### Thread Synchronization
Multiple mutex types:
- **Fork mutexes**: One per fork for resource protection
- **Print mutex**: Prevents mixed output
- **Simulation mutex**: Protects global state
- **Meal mutexes**: Individual philosopher meal tracking

## Compliance

This implementation follows:
- **42 School norminette** coding standards
- **POSIX threading** specifications
- **Memory safety** best practices
- **Thread safety** guidelines
- **Performance optimization** principles