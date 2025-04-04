import json
import matplotlib.pyplot as plt
import os

# Load JSON data
with open('results/json/results.json', 'r') as f:
    data = json.load(f)

# Group by test case
grouped = {}

for benchmark in data['benchmarks']:
    parts = benchmark['name'].split('/')
    if len(parts) < 3:
        continue  # Skip malformed names

    test_suite = parts[0]
    test_case = parts[1]
    library = parts[2]

    real_time = benchmark['real_time']

    if test_case not in grouped:
        grouped[test_case] = []

    grouped[test_case].append((library, real_time))

# Make sure the output directory exists
os.makedirs('results/json/charts', exist_ok=True)

# Generate a chart per test case
for test_case, entries in grouped.items():
    libraries, real_times = zip(*sorted(entries, key=lambda x: x[1], reverse=True))
    slowest_time = max(real_times)
    speedup_factors = [slowest_time / t for t in real_times]

    plt.figure(figsize=(30, 4))
    bars = plt.barh(libraries, real_times)

    # Customize the chart
    plt.title(f'{test_case} - Real Time Performance', fontsize=14, pad=20)
    plt.xlabel('Real Time (nanoseconds)', fontsize=12)
    plt.ylabel('JSON Library', fontsize=12)

    for bar, time, speedup in zip(bars, real_times, speedup_factors):
        width = bar.get_width()
        plt.text(width, bar.get_y() + bar.get_height()/2.,
                 f'{width:.2f} ({speedup:.2f}x)',
                 ha='left', va='center')

    plt.subplots_adjust(left=0.25, right=0.99, top=0.95, bottom=0.05)

    # Save the chart
    filename = f'results/json/charts/{test_case}_real_time.jpg'
    plt.savefig(filename, dpi=300, bbox_inches='tight', format='jpg')
    plt.close()
    print(f"Saved chart: {filename}")
