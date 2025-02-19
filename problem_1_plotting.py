import matplotlib
#matplotlib.use("Agg")
import numpy as np
import matplotlib.pyplot as plt

ham = "monte_carlo_hit-and-miss_pi.dat"

data_ham = np.loadtxt(ham, skiprows=1)  # first line is header; columns are n, estimate, rel error


mc = "monte_carlo_integration_pi.dat"

data_int = np.loadtxt(mc, skiprows=1)

ham_n = data_ham[:, 0]
ham_re = data_ham[:, 2]

mc_n = data_int[:, 0]
mc_re = data_int[:, 1]

plt.figure(figsize=(12,6))
plt.loglog(ham_n, ham_re, color = 'b', label="'Hit-and-Miss' method")
plt.loglog(mc_n, mc_re, color = 'r', label="Integral estimation method")

plt.xlabel("Number of Iterations (n)")
plt.ylabel("Relative Error")
plt.title(r"Relative Error of Monte Carlo Methods to Estimate $\pi$ as a Function of Iteration Number (Logarithmic Plot)")
plt.legend()

save_choice = input("Would you like to save the figure? (y/n): ").strip().lower()

if save_choice == "y":
    plt.savefig("PS6_#1_-_MCham_relative_error_plot.png", dpi=300)
    print("Figure saved as 'PS6_#1_-_MC_relative_error_plot.png'")

else:
    print("Figure not saved.")

plt.close()

