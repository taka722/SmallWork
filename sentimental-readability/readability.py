# TODO
from cs50 import get_string
import re


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = round(coleman_liau_index(letters, words, sentences))

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def count_letters(text):
    return len(re.findall("[a-zA-Z]", text))


def count_words(text):
    return len(text.split())


def count_sentences(text):
    return len(re.findall(r"[.!?]", text))


def coleman_liau_index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    return 0.0588 * L - 0.296 * S - 15.8


if __name__ == "__main__":
    main()
