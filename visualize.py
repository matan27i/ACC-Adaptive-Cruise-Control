#!/usr/bin/env python3
"""
ACC Simulator Visualization Script
Reads CSV output from the ACC simulator and creates plots.

Usage:
    ./acc_simulator > output.csv
    python visualize.py output.csv
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt


def visualize_acc_data(csv_file: str) -> None:
    """Load and visualize ACC simulation data."""
    df = pd.read_csv(csv_file)

    fig, axes = plt.subplots(3, 1, figsize=(10, 10), sharex=True)
    fig.suptitle('Adaptive Cruise Control Simulation Results', fontsize=14)

    # Plot 1: Distance vs Time
    ax1 = axes[0]
    ax1.plot(df['time'], df['distance'], 'b-', linewidth=2, label='Distance')
    ax1.axhline(y=15.0, color='r', linestyle='--', label='Safe Distance (15m)')
    ax1.set_ylabel('Distance (m)')
    ax1.set_title('Distance to Target Car')
    ax1.legend(loc='upper right')
    ax1.grid(True, alpha=0.3)

    # Plot 2: Positions vs Time
    ax2 = axes[1]
    ax2.plot(df['time'], df['target_pos'], 'g-', linewidth=2, label='Target Car')
    ax2.plot(df['time'], df['ego_pos'], 'b-', linewidth=2, label='Ego Car')
    ax2.set_ylabel('Position (m)')
    ax2.set_title('Vehicle Positions')
    ax2.legend(loc='upper left')
    ax2.grid(True, alpha=0.3)

    # Plot 3: Ego Velocity vs Time
    ax3 = axes[2]
    ax3.plot(df['time'], df['velocity'], 'purple', linewidth=2, label='Ego Velocity')
    ax3.set_xlabel('Time (s)')
    ax3.set_ylabel('Velocity (m/s)')
    ax3.set_title('Ego Car Velocity')
    ax3.legend(loc='upper right')
    ax3.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('acc_simulation.png', dpi=150, bbox_inches='tight')
    print(f"Plot saved to: acc_simulation.png")
    plt.show()


def main() -> None:
    if len(sys.argv) < 2:
        print("Usage: python visualize.py <csv_file>")
        print("Example: python visualize.py output.csv")
        sys.exit(1)

    csv_file = sys.argv[1]
    visualize_acc_data(csv_file)


if __name__ == "__main__":
    main()
