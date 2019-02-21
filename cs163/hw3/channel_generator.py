


"""
https://pypi.org/project/thesaurus/
pip install thesauruspip install thesaurus
"""
from thesaurus import Word
import random
import pprint
print_list = pprint.PrettyPrinter(indent=4).pprint

SERVICES = [
    "channel",
    "network",
    "broadcasting",
    "media",
    "news",
    "station",
    "company",
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
        self.search_keys_list = list()

def make_channel_name(descriptors_syns, genres_syns):
    name_words = list()

    # What is the business nature of this channel, sometimes
    if random.choice([True, False]):
        root_word = random.choice(list(descriptors_syns.keys()))
        if random.choice([True, False]):
            if descriptors_syns[root_word]:
                synonym = random.choice(descriptors_syns[root_word])
                if synonym:
                    name_words.append(synonym)
        else:
            name_words.append(root_word)

    # add a genre 
    root_word = random.choice(list(genres_syns.keys()))
    # Sometimes add a second genre, could repeat ironically
    if random.randint(0, 5) > 3:
        if genres_syns[root_word]:
            synonym = random.choice(genres_syns[root_word])
            if synonym:
                name_words.append(synonym)
    name_words.append(root_word)
    # rarely add a tertiary genre
    if random.randint(0, 10) > 8:
        root_word = random.choice(list(genres_syns.keys()))
        if genres_syns[root_word]:
            synonym = random.choice(genres_syns[root_word])
            if synonym:
                name_words.append(synonym)

    # Add a service type
    root_word = random.choice(SERVICES)
    name_words.append(root_word)

    # Ensure all lower
    for i, chars in enumerate(name_words):
        name_words[i] = chars.lower()
    
    # Join words into one string, ignoreing blanks if discovered
    return " ".join([chars for chars in name_words if chars])


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


def main(number_channels=100):
    genres_syns = generate_synonyms_dict(GENRES)
    descriptors_syns = generate_synonyms_dict(DESCRIPTORS)

    names_set = set()
    timeout_tries = number_channels * 2 # in case something get's stuck, don't run forever
    tries = 0

    while len(names_set) < number_channels and tries < timeout_tries:
        print("tries: ", tries)
        tries += 1
        new_name = make_channel_name(
            descriptors_syns=descriptors_syns,
            genres_syns=genres_syns,
        )
        names_set.add(new_name)

    print_list(names_set)

if __name__ == "__main__":
    main()
