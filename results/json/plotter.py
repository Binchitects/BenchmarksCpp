import json
import matplotlib.pyplot as plt
import numpy as np

# Read the JSON results
with open('results/json/results.json', 'r') as f:
    data = json.load(f)

# Extract benchmark data
libraries = []
real_times = []

for benchmark in data['benchmarks']:
    # Extract library name from the benchmark name
    library = benchmark['name'].split('/')[1]
    libraries.append(library)
    real_times.append(benchmark['real_time'])

# Sort the data by real time (ascending order) and reverse to put lowest at top
sorted_data = sorted(zip(real_times, libraries))
real_times, libraries = zip(*sorted_data)
libraries = list(libraries)[::-1]  # Reverse the order
real_times = list(real_times)[::-1]  # Reverse the order

# Calculate speedup factors compared to the slowest library
slowest_time = max(real_times)
speedup_factors = [slowest_time / time for time in real_times]

# Create the horizontal bar chart with much larger width and smaller height
plt.figure(figsize=(35, 4))
bars = plt.barh(libraries, real_times)

# Customize the chart
plt.title('JSON Parsing Real Time Performance', fontsize=14, pad=20)
plt.xlabel('Real Time (nanoseconds)', fontsize=12)
plt.ylabel('JSON Library', fontsize=12)

# Add value labels on the right of each bar
for bar, time, speedup in zip(bars, real_times, speedup_factors):
    width = bar.get_width()
    # Format the speedup factor to 2 decimal places
    speedup_text = f'{speedup:.2f}x'
    plt.text(width, bar.get_y() + bar.get_height()/2.,
             f'{width:.2f} ({speedup_text})',
             ha='left', va='center')

# Adjust layout to prevent label cutoff
plt.subplots_adjust(left=0.25, right=0.99, top=0.95, bottom=0.05)

# Save the plot as JPG
plt.savefig('results/json/benchmark_real_time.jpg', dpi=300, bbox_inches='tight', format='jpg')
plt.close()

print("Plot has been saved as 'benchmark_real_time.jpg'")
