# Experiment Plan

## 1. Evaluation of Compact Windows Generation

### Overview
- Total of 12 figures.
- Breakdown: 3 datasets × 2 types of outputs (number of compact windows and generation time) × 2 variables (k and n).
- Each figure compares the baseline method with our proposed method.

### Experiment Details
- **Datasets**: PAN11, OpenWebText, The Pile.
- **Outputs**: 
  - Number of Compact Windows.
  - Generation Time.
- **Variables**: 
  - Number of bins (k).
  - Document length (n).

### Experiment Setup
- Each figure's experiment is conducted on a single document per parameter set.
- Document performance is averaged over 100 or more documents.
- Document lengths (n) are set to 100, 1000, 10000, and 100000 tokens.
  - If a document exceeds the set length, only the first n tokens are considered.
  - Concate the document if its length is less than n
- Histogram Representation:
  - Each histogram has two columns: one for the baseline (Allign) and the other for our method.
  - Y-axis: Measurement (e.g., time in seconds for generation time).
  - X-axis: Variable being tested (k or n).

### Figures Configuration
1. **Dataset: PAN11**
   - Figure 1: Number of Compact Windows vs. k
   - Figure 2: Generation Time vs. k
   - Figure 3: Number of Compact Windows vs. n
   - Figure 4: Generation Time vs. n
2. **Dataset: OpenWebText**
   - Figure 5: Number of Compact Windows vs. k
   - Figure 6: Generation Time vs. k
   - Figure 7: Number of Compact Windows vs. n
   - Figure 8: Generation Time vs. n
3. **Dataset: The Pile**
   - Figure 9: Number of Compact Windows vs. k
   - Figure 10: Generation Time vs. k
   - Figure 11: Number of Compact Windows vs. n
   - Figure 12: Generation Time vs. n

## 2. Evaluation of Query Latency

### Overview
- Total of 12 figures.
- Breakdown: 3 datasets × 1 type of output (time) × 4 variables (k, θ, m (collided compact windows), number of found results).

### Experiment Details
- **Datasets**: PAN11, OpenWebText, The Pile.
- **Output**: 
  - Query Latency (Time).
- **Variables**: 
  - Number of bins (k). n = 10000 theta = 0.8 k = 16, 32, 64, 128, 256
  - Similarity threshold (θ). n = 10000 k = 64 theta = 0.5 0.6 0.7 0.8 0.9 1 q = 1000  
  - Number of collided compact windows (m).  10^7点
  - Number of found results.

### Experiment Setup
- Each figure's experiment is conducted on a single document, consistent with the previous section.
- Document performance is averaged over multiple runs.
- Dot-Line Representation:
  - Each plot has four lines: one for the baseline (Allign + IntervalScan), improved baseline (Allign + ImprovedIntervalScan), and the other for our two methods (OPH + ImprovedIntervalScan) and (OPH + ImprovedIntervalScanLongest)
  - Y-axis: Query Latency (e.g., time in seconds).
  - X-axis: Variable being tested (k, θ, m(collided cw number), or the number of found results).

### Figures Configuration
1. **Dataset: PAN11**
   - Figure 1: Query Latency vs. k
   - Figure 2: Query Latency vs. θ
   - Figure 3: Query Latency vs. m
   - Figure 4: Query Latency vs. Number of Found Results
2. **Dataset: OpenWebText**
   - Figure 5: Query Latency vs. k
   - Figure 6: Query Latency vs. θ
   - Figure 7: Query Latency vs. m
   - Figure 8: Query Latency vs. Number of Found Results
3. **Dataset: The Pile**
   - Figure 9: Query Latency vs. k
   - Figure 10: Query Latency vs. θ
   - Figure 11: Query Latency vs. m
   - Figure 12: Query Latency vs. Number of Found Results

## 3. Comparison with Baseline

### Overview
- Total of 9 figures.
- Breakdown: 3 datasets × 3 types of output (Index Time, Index Size, Query Time).

### Experiment Details
- **Datasets**: PAN11, OpenWebText, The Pile.
- **Outputs**: 
  - Index Time.
  - Index Size.
  - Query Time.
- **Fixed Parameters**: 
  - Number of bins (k) = 64.
  - Similarity threshold (θ) = 0.8.

### Experiment Setup
- Document Sample Size: Experiments are conducted on multiple documents
- Histogram Representation:
  - For Index Time and Index Size: Each histogram has two columns, one for the baseline (Allign) and the other for our methods (OPH)
  - For Query Time: Each histogram has four columns - Baseline with filter, Baseline without filter, Our method with filter, Our method without filter. (Both Report longest results)
  - Y-axis: Depending on the output (e.g., time in seconds for Index and Query Time, size in GB for Index Size).
  - X-axis: $k$ and $theta$

### Figures Configuration
1. **Dataset: PAN11** 
   - Figure 1: Index Time Comparison (vary $k$)
   - Figure 2: Index Size Comparison (vary $k$)
   - Figure 3: Query Time Comparison (vary $theta$)
   - Figure 3: Query Time Comparison (vary $k$)
2. **Dataset: OpenWebText**
   - Figure 4: Index Time Comparison
   - Figure 5: Index Size Comparison
   - Figure 6: Query Time Comparison
   - Figure 6: Query Time Comparison
3. **Dataset: The Pile**
   - Figure 7: Index Time Comparison
   - Figure 8: Index Size Comparison
   - Figure 9: Query Time Comparison
   - Figure 9: Query Time Comparison

### Additional Notes
- Ensure consistency in the experimental setup across all datasets to facilitate direct comparison.
- The inclusion of both filtered and unfiltered results in the Query Time evaluation provides a comprehensive view of the performance impact of these features.

## 4. Scalability

### Overview
- Total of 9 figures.
- Breakdown: 3 datasets × 3 types of output (Index Time, Index Size, Query Time).

### Experiment Details
- **Datasets**:PAN11 (maybe excluded due to its 1GB small size) OpenWebText, The Pile 
- **Outputs**: 
  - Index Time.
  - Index Size.
  - Query Time.
- **Fixed Parameter**: 
  - Similarity threshold (θ) = 0.8.

### Experiment Setup
- Document Sample Size: Experiments are conducted on large-scale documents (10,000, 100,000, 1,000,000).
- Histogram Representation:
  - Each histogram has 3 columns, representing different numbers of bins (k): 32, 64, and 128.
  - Y-axis: Depending on the output (e.g., time in seconds for Index and Query Time, size in GB for Index Size).
  - X-axis: Document sample size (10K, 100K, 1M, 10M).
- All experiments are conducted with the filter enabled to emphasize the method's efficiency in handling large datasets.

### Figures Configuration
1. **Dataset: OpenWebText**
   - Figure 1: Index Time Scalability
   - Figure 2: Index Size Scalability
   - Figure 3: Query Time Scalability
   - Figure 3: Query Time Scalability (lines to represent different $\theta$)
2. **Dataset: OpenWebText**
   - Figure 4: Index Time Scalability
   - Figure 5: Index Size Scalability
   - Figure 6: Query Time Scalability
3. **Dataset: The Pile**
   - Figure 7: Index Time Scalability
   - Figure 8: Index Size Scalability
   - Figure 9: Query Time Scalability   

### Additional Notes
- The scalability tests are crucial for demonstrating the algorithm's performance on large datasets.
- Maybe we exclude PAN11, which does not align with the scalability focus of this section.

