# Project Structure

This document describes the organization of the Dining Philosophers project.

## Directory Structure

```
philo/
├── include/           # Header files
│   └── philo.h       # Main header with all declarations
├── src/              # Source code organized by functionality
│   ├── core/         # Core application logic
│   │   ├── philo.c   # Main entry point
│   │   ├── init.c    # Initialization functions
│   │   ├── threads.c # Thread management
│   │   └── routine.c # Main philosopher routine
│   ├── actions/      # Philosopher actions
│   │   ├── actions.c     # Eating, sleeping, thinking actions
│   │   ├── actions_utils.c # Action utilities
│   │   └── forks.c       # Fork management
│   ├── monitor/      # Simulation monitoring
│   │   ├── monitor.c     # Main monitoring logic
│   │   └── monitor_utils.c # Monitoring utilities
│   └── utils/        # General utilities
│       ├── utils.c       # Basic utility functions
│       ├── getters.c     # Getter functions
│       ├── log_utils.c   # Logging utilities
│       ├── sim_utils.c   # Simulation utilities
│       ├── timing.c      # Time-related functions
│       └── special_cases.c # Edge case handling
├── obj/              # Object files (mirrors src structure)
├── build/            # Build artifacts (future use)
├── docs/             # Documentation
├── Makefile          # Build configuration
├── README.md         # Project description
└── LICENSE           # License file
```

## Build System

The project uses a modern Makefile with the following features:

- **Organized object files**: Object files are stored in `obj/` directory, mirroring the source structure
- **Automatic directory creation**: Build directories are created automatically
- **Clean separation**: Source and build artifacts are kept separate
- **Debug support**: Use `make debug` for debug builds
- **Help system**: Use `make help` to see available targets

### Available Make Targets

- `make` or `make all` - Build the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Rebuild everything
- `make debug` - Build with debug flags
- `make help` - Show help message

## Code Organization

### Core Module (`src/core/`)
Contains the main application logic and thread management.

### Actions Module (`src/actions/`)
Handles all philosopher actions (eating, fork management, etc.).

### Monitor Module (`src/monitor/`)
Responsible for monitoring the simulation state and detecting end conditions.

### Utils Module (`src/utils/`)
Contains utility functions used throughout the application.

## Benefits of This Structure

1. **Maintainability**: Related code is grouped together
2. **Scalability**: Easy to add new modules or features
3. **Clean Builds**: Object files are separated from source code
4. **Clear Dependencies**: Module boundaries are well-defined
5. **Professional Organization**: Follows standard C project conventions
