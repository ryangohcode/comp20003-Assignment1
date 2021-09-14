import sys
import matplotlib.pyplot as plt
import matplotlib

sys.stdin.reconfigure(encoding='utf-8-sig')
colors = ['lawngreen', 'g', 'teal', 'cyan', 'deepskyblue', 'dodgerblue', 'navy', 'indigo', 'violet', 'm', 'b']
matplotlib.use('gtk3agg')

for line in sys.stdin:
    if line[0] != '@':
        print(line, end='')
    elif line[1] == 'W':
        n, *coord = line[2:].split()
        n, (x, y) = int(n), map(float, coord)

        if n == -1:
            plt.plot(x, y, marker='.', mfc='black', mew=0, alpha=0.5, label=n)
        else:
            plt.plot(x, y, marker='.', mfc=colors[n % 11], mew=0, alpha=0.5, label=n)
        
    elif line[1] == 'E':
        n, *coord = line[2:].split()
        n, (x1, y1, x2, y2) = int(n), map(float, coord)
        dx, dy = x2-x1, y2-y1
        
        plt.plot(x1, y1, 'yo', alpha=0.5)
        plt.plot(x2, y2, 'yo', alpha=0.5)
        plt.arrow(x1, y1, dx, dy, length_includes_head=True, width=0.1, fc='black', 
                  shape='left', label='1', alpha=0.2, ec=None)
        plt.annotate(n, (x1 + dx/2, y1 + dy/2), c='red')

plt.show()
