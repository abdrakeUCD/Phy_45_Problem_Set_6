import matplotlib
#matplotlib.use("Agg")
import numpy as np
import matplotlib.pyplot as plt

filename = "monte_carlo_hit-and-miss_pi.dat"

data = np.loadtxt(filename, skiprows=1)  # first line is header; columns are n, estimate, rel error

n_values = data[:, 0]
relative_error_values = data[:, 2]

plt.figure(figsize=(12,6))
plt.loglog(n_values, relative_error_values, label=r"$\frac{|\pi - \pi_{\mathrm{estimate}}|}{\pi}$")

plt.xlabel("Number of Iterations (n)")
plt.ylabel("Relative Error")
plt.title(r"Relative Error of Monte Carlo 'Hit-and-Miss' Method to Estimate $\pi$ as a Function of Iteration Number (Logarithmic Plot)")
plt.legend()

save_choice = input("Would you like to save the figure? (y/n): ").strip().lower()

if save_choice == "y":
    plt.savefig("PS6_#1_-_MCham_relative_error_plot.png", dpi=300)
    print("Figure saved as 'PS6_#1_-_MCham_relative_error_plot.png'")

else:
    print("Figure not saved.")

plt.close()

