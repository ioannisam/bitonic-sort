import os
import matplotlib.pyplot as plt

FILE_PATH = os.path.join(os.path.dirname(__file__), 'results.txt')

SAVE_DIR = os.path.join(os.path.dirname(__file__), '../assets')
SAVE_PATH1 = os.path.join(SAVE_DIR, 'performance.png')
SAVE_PATH2 = os.path.join(SAVE_DIR, 'speed.png')

data = {}
curr_p = None

# read and parse the data from results.txt
with open(FILE_PATH, 'r') as file:
    for line in file:
        line = line.strip()
        if line.startswith('NUMBER OF PROCESSES'):
            curr_p = int(line.split(': ')[1])
            data[curr_p] = {'q': [], 'time': []}
        elif line.startswith('q='):
            curr_q = int(line.split('=')[1])
            curr_t = float(next(file).strip().split(': ')[1])
            data[curr_p]['q'].append(curr_q)
            data[curr_p]['time'].append(curr_t)

rainbow = ['red', 'orange', 'yellow', 'green', 'teal', 'blue', 'purple']

# performance plot
plt.figure(figsize=(10, 6))

for i, (processes, values) in enumerate(data.items()):
    color = rainbow[i%len(rainbow)]
    plt.plot(values['time'], values['q'], label=f'p={processes}', color=color)

plt.xlabel('Execution Time (s)')
plt.ylabel('q value')
plt.title('Execution Time vs q value for different number of processes')
plt.legend()
plt.grid(True)

plt.savefig(SAVE_PATH1)
plt.show()

# numbers per second plot
plt.figure(figsize=(10, 6))

for i, (processes, values) in enumerate(data.items()):
    color = rainbow[i%len(rainbow)]
    sorted_numbers_per_second = []
    for q, time in zip(values['q'], values['time']):
        N = 2 ** (processes + q)
        sorted_per_second = N / time
        sorted_numbers_per_second.append(sorted_per_second)
    plt.plot(values['q'], sorted_numbers_per_second, label=f'p={processes}', color=color)

plt.xlabel('q value')
plt.ylabel('Numbers Sorted per Second')
plt.title('q value vs Numbers Sorted per Second for different number of processes')
plt.legend()
plt.grid(True)

plt.savefig(SAVE_PATH2)
plt.show()