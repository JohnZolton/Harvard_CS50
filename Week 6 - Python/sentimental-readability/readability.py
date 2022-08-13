# TODO
from cs50 import get_string

text = get_string("paste in your text: ")

#formula is 0.0588 * L - 0.296 * S - 15.8
# L = average number of letters /100 words
# S = average number of sentences/100 words

letters = 0
words = 1
sentences = 0
#count number of letters
for i in range(len(text)):
    #count sentences
    if (ord(text[i]) == ord('!') or ord(text[i]) == ord('.') or ord(text[i]) == ord('?')):
        sentences +=1
    #count words
    elif ord(text[i]) == ord(" "):
        words += 1
    #Count letters
    else:
        letters += 1


l = (letters/words)*100
s = (sentences/words)*100
x = .0588*l - 0.296*s - 15.8
score = int(x)
if score <1:
    print("Before Grade 1")

elif score >= 16:
    print("Grade 16+")

elif (score >= 1 and score <=15):
    print(f"Grade {score}")
