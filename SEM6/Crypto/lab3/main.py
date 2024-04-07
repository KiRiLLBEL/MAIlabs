import random
import string

import requests

def get_words(url, target_length):
    response = requests.get(url)
    words = response.json()

    text = ""
    for word in words:
        if len(text) + len(word) + 1 > target_length:
            break
        text += word + " "

    text = text.ljust(target_length)

    return text

def read_chars_from_file(filename, target_length):
    with open(filename, 'r') as file:
        text = file.read(target_length)
    return text

def generate_random_text(target_length):
    chars = string.ascii_letters + string.punctuation + string.digits
    return ''.join(random.choice(chars) for _ in range(target_length))

def calculate_ratio(text1, text2):
    if len(text1) > len(text2):
        text1, text2 = text2, text1

    matching_chars = sum(c1 == c2 for c1, c2 in zip(text1, text2))

    total_chars = len(text1) + len(text2)

    ratio = matching_chars / total_chars

    return ratio

def backup_text(text, filename):
    with open(filename, 'w') as file:
        file.write(text)

url = "https://random-word-api.herokuapp.com/word?number=1000000"
target_length = 1000

wordsText1 = get_words(url, target_length)
wordsText2 = get_words(url, target_length)

naturalText1 = read_chars_from_file("text1.txt", target_length)
naturalText2 = read_chars_from_file("text2.txt", target_length)

charsText1 = generate_random_text(target_length)
charsText2 = generate_random_text(target_length)

ratio1 = calculate_ratio(naturalText1, naturalText2)
ratio2 = calculate_ratio(naturalText1, charsText1)
ratio3 = calculate_ratio(naturalText1, wordsText1)
ratio4 = calculate_ratio(charsText1, charsText2)
ratio5 = calculate_ratio(wordsText1, wordsText2)

with open("result1.txt", 'w') as file:
    file.writelines(map(lambda x: str(x) + '\n', [ratio1, ratio2, ratio3, ratio4, ratio5]))

backup_text(naturalText1, "naturalText1")
backup_text(naturalText2, "naturalText2")
backup_text(wordsText1, "wordsText1")
backup_text(wordsText2, "wordsText2")
backup_text(charsText1, "charsText1")
backup_text(charsText2, "charsText2")