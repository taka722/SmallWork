# TODO


def main():
    height = get_int("Enter the height of the pyramid (1-8): ")
    for i in range(1, height + 1):
        # Print the first pyramid
        print(" " * (height - i) + "#" * i, end="  ")
        # Print the second pyramid
        print("#" * i)


def get_int(prompt):
    while True:
        try:
            height = int(input(prompt))
            if 1 <= height <= 8:
                return height
            else:
                print("Height should be between 1 and 8, inclusive.")
        except ValueError:
            print("Please enter a positive integer.")


# Call the main function to execute the program
if __name__ == "__main__":
    main()
