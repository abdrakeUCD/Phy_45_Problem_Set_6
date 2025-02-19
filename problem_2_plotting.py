import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from scipy.stats import norm


file_1 = "outputs_nskip_1.dat"
data_1 = np.loadtxt(file_1)


file_2 = "outputs_nskip_2.dat"
data_2 = np.loadtxt(file_2)


file_5 = "outputs_nskip_5.dat"
data_5 = np.loadtxt(file_5)


file_10 = "outputs_nskip_10.dat"
data_10 = np.loadtxt(file_10)


file_50 = "outputs_nskip_50.dat"
data_50 = np.loadtxt(file_50)


file_100 = "outputs_nskip_100.dat"
data_100 = np.loadtxt(file_100)


x = np.linspace(-5, 5, 3000)
y = norm.pdf(x, loc=0, scale=1)

fig, axes = plt.subplots(2, 3, figsize=(15, 10))

axes[0, 0].hist(data_1, bins=32, density=True, alpha=0.6, color='b', label="nskip=1")
axes[0, 1].hist(data_2, bins=32, density=True, alpha=0.6, color='b', label="nskip=2")
axes[0, 2].hist(data_5, bins=32, density=True, alpha=0.6, color='b', label="nskip=5")
axes[1, 0].hist(data_10, bins=32, density=True, alpha=0.6, color='b', label="nskip=10")
axes[1, 1].hist(data_50, bins=32, density=True, alpha=0.6, color='b', label="nskip=50")
axes[1, 2].hist(data_100, bins=32, density=True, alpha=0.6, color='b', label="nskip=100")

for ax in axes.flatten():
    ax.plot(x, y, 'r-', linewidth=2, label="Standard Normal")
    ax.set_xlabel("Value")
    ax.set_ylabel("Density")
    ax.legend()

axes[0, 0].set_title("nskip = 1")
axes[0, 1].set_title("nskip = 2")
axes[0, 2].set_title("nskip = 5")
axes[1, 0].set_title("nskip = 10")
axes[1, 1].set_title("nskip = 50")
axes[1, 2].set_title("nskip = 100")

plt.tight_layout()
plt.show()

save_choice = input("Would you like to save the figure? (y/n): ").strip().lower()
if save_choice == "y":
    plt.savefig("PS6_#2_-_histograms.png", dpi=300)
    print("Figure saved as 'PS6_#2_-_histograms.png'")
else:
    print("Figure not saved.")

plt.close()
