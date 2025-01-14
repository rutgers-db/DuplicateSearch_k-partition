import sys

def parse_ranges(line):
    """
    Convert a line of text into a list of tuples (start, end).
    """
    ranges = []
    pairs = line.strip().split(" ")
    for pair in pairs:
        if pair:
            start, end = map(int, pair.strip("()").split(","))
            ranges.append((start, end))
    return ranges

def range_overlap(range_a, range_b):
    """
    Calculate the overlap between two ranges.
    """
    return max(0, min(range_a[1], range_b[1]) - max(range_a[0], range_b[0]) + 1)

def calculate_overlap(ranges_a, ranges_b):
    """
    Calculate total overlap between two lists of ranges.
    """
    total_overlap = 0
    for range_a in ranges_a:
        for range_b in ranges_b:
            total_overlap += range_overlap(range_a, range_b)
    return total_overlap

def calculate_total_range(ranges):
    """
    Calculate the total range covered by a list of ranges.
    """
    total = 0
    for start, end in ranges:
        total += end - start + 1
    return total

def average_overlap_rate(file_a, file_b):
    """
    Calculate the average overlap rate between two files.
    """
    with open(file_a, 'r') as f_a, open(file_b, 'r') as f_b:
        total_overlap_rate = 0
        line_count = 0

        for line_a, line_b in zip(f_a, f_b):
            ranges_a = parse_ranges(line_a)
            ranges_b = parse_ranges(line_b)
            total_overlap = calculate_overlap(ranges_a, ranges_b)
            total_range_b = calculate_total_range(ranges_b)    # this is for recall
            # total_range_a = calculate_total_range(ranges_a)  # this is for precision
            
            if total_range_b > 0:
                overlap_rate = total_overlap / total_range_b
                total_overlap_rate += overlap_rate
                line_count += 1

        return total_overlap_rate / line_count if line_count > 0 else 0


if len(sys.argv) != 3:
    print("Usage: python script.py file_a.txt file_b.txt")
    sys.exit(1)

file_a = sys.argv[1]  # Get the file path for file A from command-line arguments
file_b = sys.argv[2]  # Get the file path for file B from command-line arguments
print("Average Overlap Rate:", average_overlap_rate(file_a, file_b))
