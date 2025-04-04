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


##### Score
os.makedirs('results/json/charts/speed_score/', exist_ok=True)

for test_case, entries in grouped.items():
    if len(entries) < 2:
        continue  # skip if there's nothing to compare

    # Sort entries by real_time ascending
    entries.sort(key=lambda x: x[1])
    slowest_time = entries[-1][1]

    libraries = []
    scores = []

    for lib, rt in entries:
        score = slowest_time / rt
        libraries.append(lib)
        scores.append(score)

    # Plot the chart
    plt.figure(figsize=(12, 4))
    bars = plt.barh(libraries, scores, color='teal')

    for bar, score in zip(bars, scores):
        width = bar.get_width()
        plt.text(width + 0.01, bar.get_y() + bar.get_height()/2,
                 f'{score:.2f}x', ha='left', va='center', fontsize=9)

    plt.xlabel('Relative Speed (Higher is Better)')
    plt.title(f'Speed Scores for Test Case: {test_case}')
    plt.xlim(0, max(scores) * 1.1)

    plt.tight_layout()
    safe_name = test_case.replace('/', '_').replace(' ', '_')
    filename = f'results/json/charts/speed_score/score_{safe_name}.jpg'
    plt.savefig(filename, dpi=300)
    plt.close()

    print(f"Saved: {filename}")
    
    
    
#### Indentation effect
from collections import defaultdict
import numpy as np

# Step 1: Group data by library
library_data = defaultdict(lambda: {'indented': [], 'non_indented': []})

for test_case, entries in grouped.items():
    is_indented = 'indented' in test_case.lower()
    for lib, rt in entries:
        key = 'indented' if is_indented else 'non_indented'
        library_data[lib][key].append(rt)

# Step 2: Compute slowdown factors
libraries = []
slowdown_factors = []

for lib, results in library_data.items():
    if not results['indented'] or not results['non_indented']:
        continue

    avg_indented = sum(results['indented']) / len(results['indented'])
    avg_non_indented = sum(results['non_indented']) / len(results['non_indented'])
    slowdown = avg_indented / avg_non_indented

    libraries.append(lib)
    slowdown_factors.append(slowdown)

# Step 3: Sort by slowdown
sorted_data = sorted(zip(slowdown_factors, libraries), reverse=True)
slowdown_factors, libraries = zip(*sorted_data)

# Step 4: Plot slowdown factors
plt.figure(figsize=(14, 6))
bars = plt.bar(libraries, slowdown_factors, color='darkorange')

# Add labels above bars
for i, slowdown in enumerate(slowdown_factors):
    plt.text(i, slowdown + 0.01, f'{slowdown:.2f}x',
             ha='center', va='bottom', fontsize=10, fontweight='bold')

plt.ylabel('Indentation Slowdown Factor (Indented / Non-Indented)')
plt.title('Indentation Overhead Per JSON Library')
plt.axhline(1.0, color='gray', linestyle='--', linewidth=1)
plt.xticks(rotation=30, ha='right')

plt.tight_layout()
plt.savefig('results/json/charts/indentation_slowdown_per_library.jpg', dpi=300)
plt.close()

print("Saved: results/json/charts/indentation_slowdown_per_library.jpg")




#### Total score
from collections import defaultdict

# Step 1: Accumulate total scores per library
library_scores = defaultdict(float)

for test_case, entries in grouped.items():
    if len(entries) < 2:
        continue  # skip if only one library

    # Sort by real_time ascending
    entries.sort(key=lambda x: x[1])
    slowest_time = entries[-1][1]

    for lib, rt in entries:
        score = slowest_time / rt
        library_scores[lib] += score  # add to total

# Step 2: Sort libraries by total score
sorted_scores = sorted(library_scores.items(), key=lambda x: x[1], reverse=True)
libraries, total_scores = zip(*sorted_scores)

# Step 3: Plot overall score chart
plt.figure(figsize=(14, 6))
bars = plt.bar(libraries, total_scores, color='slateblue')

# Add score labels
for bar, score in zip(bars, total_scores):
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height,
             f'{score:.2f}', ha='center', va='bottom', fontsize=9)

plt.ylabel('Total Performance Score (Sum over all test cases)')
plt.title('Overall Performance Score per Library\n(Higher is Better)')
plt.xticks(rotation=30, ha='right')

plt.tight_layout()
plt.savefig('results/json/charts/overall_library_scores.jpg', dpi=300)
plt.close()

print("Saved: results/json/charts/overall_library_scores.jpg")