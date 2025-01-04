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
        if line.startswith('WHEN p = '):
            curr_p = int(line.split('=')[1].strip())
            data[curr_p] = {'q': [], 't': [], 'nps': []}
        elif line.startswith('q = '):
            curr_q = int(line.split('=')[1].strip())
            curr_t = float(next(file).strip().split(': ')[1])
            N = 2 ** (curr_p + curr_q)
            curr_nps = N / curr_t

            data[curr_p]['q'].append(curr_q)
            data[curr_p]['t'].append(curr_t)
            data[curr_p]['nps'].append(curr_nps)

rainbow = ['black', 'red', 'orange', 'yellow', 'green', 'blue', 'indigo', 'violet']

# performance plot
plt.figure(figsize=(10, 6))

for i, (p, values) in enumerate(data.items()):
    color = rainbow[i % len(rainbow)]
    plt.plot(values['t'], values['q'], label=f'p={p}', color=color)

plt.title('Execution Time vs q value for different number of processes')
plt.xlabel('Execution Time (s)')
plt.ylabel('q value')
plt.grid(True)
plt.legend()

plt.savefig(SAVE_PATH1)
plt.show()

# speed plot
plt.figure(figsize=(10, 6))

for i, (p, values) in enumerate(data.items()):
    color = rainbow[i % len(rainbow)]
    plt.plot(values['q'], values['nps'], label=f'p={p}', color=color)

plt.title('q value vs Numbers Sorted per Second for different number of processes')
plt.xlabel('q value')
plt.ylabel('Numbers Sorted per Second')
plt.grid(True)
plt.legend()

plt.savefig(SAVE_PATH2)
plt.show()