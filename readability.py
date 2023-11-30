from cs50 import get_string

text = get_string('Text: ')

letters = 0
words = 0
sentences = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    if text[i] in [' ']:
        words += 1
    if text[i] in ['.', '!', '?']:
        sentences += 1
words += 1

grade = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)

if grade >= 16:
    print('Grade 16+')
elif grade < 1:
    print('Before Grade 1...')
else:
    print('Grade', grade)
