# coleman - Liau index
def main():
    textinput = input("Text: ")
    # calcualte nolof words, letters, sentences
    letters = count_letters(textinput)
    words = count_words(textinput)
    sentences = count_sentences(textinput)
    # calcualte the coleman-liau index
    index = indexCalculate(letters, words, sentences)
    #display index in required format
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")



def count_letters(inputline):
    letters = 0
    for i in range(len(inputline)):
        temp = ord(inputline[i])
        if (temp >= 65 and temp <= 90) or (temp >= 97 and temp <= 122):
            letters += 1
    return letters

def count_words(inputline):
    words = 0
    for i in range(len(inputline)):
        temp = inputline[i]
        if(temp == " "):
            words += 1
    return words+1

def count_sentences(inputline):
    sentences = 0
    for i in range(len(inputline)):
        temp = inputline[i]
        if temp == "." or temp == "?" or temp == "!":
            sentences += 1
    return sentences

def indexCalculate(letters, words, sentences):
    # calculate letters and sentences per 100 words 
    L = letters/words * 100
    S = sentences/words * 100
    # calcualre the index using the formula
    index = 0.0588*L - 0.296*S - 15.8
    # changing the index to an integer
    exactindex = round(index)

    return exactindex




if __name__ == "__main__":
    main()
