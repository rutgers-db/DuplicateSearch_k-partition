# Estimation Accuracy of Min-Hash and OPH

## Overview
This folder contains the implementations and visualizations of the estimated Jaccard similarity using Min-Hash and One Permutation Hashing (OPH) techniques. We focus on demonstrating how the estimated similarity behaves across different configurations, especially with varying numbers of hash functions $k$.

## Min-Hash Simulation
Min-Hash is a widely used technique for estimating the Jaccard similarity between datasets. Given a threshold $\theta$, two text datasets $T$ and $S$ are considered similar if $\hat{J}_{T, S} \geq \theta$. The probability of a match reported by Min-Hash depends on the actual Jaccard similarity, represented by the number of collided min-hashes $m$, which is calculated as:
$$m = \sum_{i=1}^{k}\mathbf{1}\{h_i(T)=h_i(S)\}$$
The probability distribution for this estimation is given by:
$$\textbf{Pr}(\hat{J}_{T, S} \geq \frac{m}{k}) = 1 - \sum_{j=0}^{m-1} \binom{k}{j} (J_{T, S})^j (1 - J_{T, S})^{k-j}$$
where $m = \lceil k\theta \rceil$.

## OPH Simulation
The OPH method is also explored to understand its performance relative to Min-Hash. For this method, we simulate the probability distribution for $T$ and $S$ being reported as similar using the following setup:
- **Data Generation**: Randomly generated 1000 pairs of text sets for each of 1000 Jaccard similarity values ranging from 0 to 1. Each pair has a union size of 1000, ensuring the size of two sets in a pair are nearly equal.
- **Hashing and Estimation**: Applied a random hash function to generate the OPH min-hash and calculated $\hat{J}_{T, S}$.
- **Frequency Calculation**: The frequency of pairs where $\hat{J}_{T, S} \geq 0.5$ was recorded for each Jaccard similarity point, averaged over 100 simulations.

## Visualization
The distributions were visualized and smoothed using a Savitzky-Golay filter with a window size of 11 and a polynomial order of 3. The figures, which can be found in `plot_KMS_varyK.gnu` and `plot_KMSAndOPh.gnu`, demonstrate the accuracy of OPH estimation in Jaccard similarity, closely matching the curve of $k$-mins.

## False Positive and False Negative Evaluation
False positives arise when the actual Jaccard similarity $J_{T, S}$ is below the threshold $\theta$, yet the estimated similarity $\hat{J}_{T, S}$ meets or exceeds $\theta$. Conversely, false negatives occur when $J_{T, S}$ is above $\theta$ but $\hat{J}_{T, S}$ falls short. If the Jaccard similarity $J_{T, Q}$ follows a uniform distribution over the interval [0,1] (i.e., $J_{T, Q} \sim U(0,1)$), the rates are estimated as follows:

- **False Positive Rate (FP)**:
$$FP = \int_0^\theta \text{Pr}(\hat{J}_{T, S} \geq \theta) \cdot \text{f}(J_{T, Q}) \, dJ_{T, Q}$$
- **False Negative Rate (FN)**:
$$FN = \int_\theta^1 (1 - \text{Pr}(\hat{J}_{T, S} \geq \theta)) \cdot \text{f}(J_{T, Q}) \, dJ_{T, Q}$$

## Files
- **Data Generation**: `KMS_probdist.ipynb`
- **Plot Scripts**: `plot_KMS_varyK.gnu`, `plot_KMSAndOPh.gnu`
