


"""
Dependencies:

https://pypi.org/project/thesaurus/
pip install thesaurus

"""

from thesaurus import Word
import random
import pprint
print_list = pprint.PrettyPrinter(indent=4).pprint

OUTPUT_PATH = "U:/development/practice/school/cs163/hw3/channels.txt"
FILE_HEADER = "#CHANNELS-DUMP"
CHANNEL_HEADER = "#CHANNEL-OBJECT"
CHANNEL_FOOTER = "#CHANNEL-END"

DELIM = "\n"

SERVICES = [
    "channel",
    "network",
    "broadcasting",
    "media",
    "news",
    "station",
    "radio",
    "services",
]

GENRES = [
    "movies",
    "sports",
    "Absurdist",
    "surreal",
    "whimsical",
    "Action",
    "Adventure",
    "Comedy",
    "Crime",
    "Drama",
    "Fantasy",
    "Historical",
    "Horror",
    "Magical",
    "Mystery",
    "Paranoid",
    "Philosophical",
    "Political",
    "Romance",
    "Saga",
    "Satire",
    "Science",
    "Social",
    "Speculative",
    "Thriller",
    "Urban",
    "Western",
    "educational",
    "animation",
    "cartoons",
    "childrens",
    "puppetry",
    "Adult",
    "Art",
    "Action",
    "Adventure",
    "Courtroom",
    "Detective",
    "Docudrama",
    "Fantasy",
    "Historical",
    "Legal",
    "Medical ",
    "Police",
    "Philosophical",
    "Political",
    "Science-fiction",
    "Teen",
    "Thriller",
    "Western",
]

DESCRIPTORS = [
    "National",
    "Universal",
    "Premium",
    "Live",
    "fantastic",
    "local",
    "public",
    "digital",
    "official",
    "independent",
    "foreign",
    "international",
    "original",
]

class Channel(object):
    def __init__(self):
        self.name = ""
        self.description = ""
        self.notes = ""
        self.rating = ""
        self.search_keys = set()

    def generate_search_keys(self, syns_dict):
        for chars in self.name.split(" "):
            self.search_keys.add(chars)
            if chars in syns_dict:
                if syns_dict[chars]:
                    synonym = random.choice(syns_dict[chars])
                    if synonym:
                        self.search_keys.add(synonym)
        return

    def generate_notes(self):
        notes_words = list()
        doge_vocab = ["many", "much", "very"]
        notes_words.append("wow.")
        for i, term in enumerate(list(self.search_keys)):
            notes_words.append(doge_vocab[i % len(doge_vocab)])
            notes_words.append(term + ".")
        self.notes = " ".join(notes_words) + " what is " + next(iter(self.search_keys)) + "?"

    def generate_description(self):
        desc_words = list()
        name_words = self.name.split(" ")
        desc_words.append("This is a")
        desc_words.append(name_words[-1])
        desc_words.append("service about")
        desc_words.append(name_words[-2])
        desc_words.append("that is very")
        desc_words.append(name_words[1])
        self.description = " ".join(desc_words)
        return

    def generate_rating(self):
        self.rating = random.randint(1, 5)

    def generate_properties(self, syns_dict):
        self.generate_search_keys(syns_dict)
        self.generate_notes()
        self.generate_description()
        self.generate_rating()

    def randomize_channel_name(self, syns_dict):
        name_words = list()

        # What is the business nature of this channel, sometimes
        if random.choice([True, False]):
            root_word = random.choice(DESCRIPTORS)
            if random.choice([True, False]):
                if syns_dict[root_word]:
                    synonym = random.choice(syns_dict[root_word])
                    if synonym:
                        name_words.append(synonym)
            else:
                name_words.append(root_word)

        # add a genre 
        root_word = random.choice(GENRES)
        # Sometimes add a second genre, could repeat ironically
        if random.randint(0, 5) > 3:
            if syns_dict[root_word]:
                synonym = random.choice(syns_dict[root_word])
                if synonym:
                    name_words.append(synonym)
        # rarely add a tertiary genre
        if random.randint(0, 10) > 8:
            root_word = random.choice(GENRES)
            if syns_dict[root_word]:
                synonym = random.choice(syns_dict[root_word])
                if synonym:
                    name_words.append(synonym)
        name_words.append(root_word)

        # Add a service type
        root_word = random.choice(SERVICES)
        name_words.append(root_word)

        # Ensure all lower
        for i, chars in enumerate(name_words):
            name_words[i] = chars.lower()
        
        # Join words into one string, ignoreing blanks if discovered
        self.name = " ".join(name_words)
        # was somehow getting blank words occasionally
        # remove excess whitespace
        self.name = " ".join(self.name.split())

    def write_to_file(self, outf):
        text_dump_words = [
            "", # To separate from previous object
            CHANNEL_HEADER,
            self.name,
            self.description,
            self.notes,
            str(self.rating),
        ]
        # Write the search keys between key section tags
        for search_key in self.search_keys:
            text_dump_words.append(search_key)
        text_dump_words.append(CHANNEL_FOOTER)

        # Join the properties into one string joined with the delimiter
        text_dump = DELIM.join(text_dump_words)
        outf.write(text_dump)

def generate_synonyms_dict(words_list):
    synonyms_dict = dict()
    for chars in words_list:
        try:
            w = Word(chars)
            syns = w.synonyms(
                relevance=3,
                form='common',
                )
            synonyms_dict[chars] = syns
        except:
            synonyms_dict[chars] = [chars,]

    return synonyms_dict


def main(number_channels=500):
    syns_dict = generate_synonyms_dict(DESCRIPTORS + GENRES)

    names_set = set()
    channel_list = list()
    timeout_tries = number_channels * 2 # in case cannot come up with original names, don't run forever. 
    tries = 0

    while len(names_set) < number_channels and tries < timeout_tries:
        print("tries: ", tries)
        tries += 1
        new_channel = Channel()
        new_channel.randomize_channel_name(syns_dict=syns_dict)
        # If this is not an original name, don't use it
        if new_channel.name in names_set:
            continue
        names_set.add(new_channel.name)
        new_channel.generate_properties(syns_dict=syns_dict)
        channel_list.append(new_channel)

    with open(OUTPUT_PATH, "w") as outf:
        outf.write(FILE_HEADER + DELIM)
        for channel in channel_list:
            channel.write_to_file(outf)


if __name__ == "__main__":
    main()
