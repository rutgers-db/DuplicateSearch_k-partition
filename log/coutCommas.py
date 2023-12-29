def count_commas_in_file(file_path):
    """
    Count the number of commas in a file.
    :param file_path: Path to the file containing the text.
    :return: The number of commas in the file.
    """
    try:
        with open(file_path, 'r') as file:
            text = file.read()
            return text.count(',')
    except FileNotFoundError:
        return "File not found. Please check the file path."

def main():
    file_path = 'bsearch_omp.txt'  # Replace with your file path if different
    commas_count = count_commas_in_file(file_path)
    print(f"Total number of commas in the file: {commas_count}")

if __name__ == "__main__":
    main()
