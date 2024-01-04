# TODO
from cs50 import get_string


def main():
    card_num = get_string("Number: ")
    length = get_length(card_num)

    if length not in [13, 15, 16] or not check_sum(card_num):
        print("INVALID")
    else:
        print(card_type(card_num, length))


def check_sum(number):
    sum = 0
    num_str = str(number)
    # Reverse the credit card number and process digits
    for i, digit in enumerate(reversed(num_str)):
        digit = int(digit)
        if i % 2 == 0:
            sum += digit
        else:
            digit = digit * 2
            sum += (digit // 10) + (digit % 10)
    return sum % 10 == 0


def card_type(number, length):
    num_str = str(number)
    if length == 15 and (num_str.startswith("34") or num_str.startswith("37")):
        return "AMEX"
    elif length == 16 and (50 < int(num_str[:2]) < 56):
        return "MASTERCARD"
    elif (length == 13 or length == 16) and num_str.startswith("4"):
        return "VISA"
    else:
        return "INVALID"


def get_length(number):
    return len(str(number))


if __name__ == "__main__":
    main()
