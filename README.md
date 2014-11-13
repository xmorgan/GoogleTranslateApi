GoogleTranslateApi
==================
// Google Translate API description
// Updated: 11/11/14

// Reverse engineering of the Google Website Translator gadget's api
// The gadget uses HTTP GET Method to fech data from the server

// Base Url: https://translate.google.com/translate_a/single
// Example query: ?client=t&sl=en&tl=fr&hl=en&dt=bd&dt=ex&dt=ld&dt=md&dt=qc&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=sw&q=Hello

/////////////////////////////////////////////////////////////////////
// The format of the Translate's reply is described using the BNF-syntax

<HttpGetReply> ::=
[
 [<Translation>*, <Translit>],
 [<PosDict>*],
 lang_source_abrev,            // iso639-1 source language code (ex. en | fr)
 ?,
 ?(!),
 ?(!),
 ?,
 ?,
 ?(!),
 ?,
 ?,
 [<SynonymDict>*],
 [<DefineDict>*],
 [<ExampleDict>],
 [<SeeAlsoDict>],
 server_time?
]

<Translation> ::= [         // Pair of the translated sentence and it's original
    sentence_target,
    sentence_source
]

<Translit> ::= [            // Transliteration of the translated text and original
    ?,
    ?,
    translit_target,
    translit_source
]

<PosDict> ::= [             // Dictionary that contains Part's Of the Speech, word transl and retransl
    pos_name_hl,
    [word_target*],
    [<PosDictEntry>*],
    word_source_base_form,  // infinitif
    <PosDictEnum>           // associates pos_name_hl with a number
]

<PosDictEntry> ::= [
    word_target,
    [word_retranslated*],      // list of retranslations
    [synset_id*],              // list of num's
    score,                     // how common the word is
    previous_word_target       // le article - lol :D
]

<SynDict> ::= [             // Dictionary that contains synonyms of the source word
    pos_name,               // can be empty
    [<SynDictEntry>*],
    word_base_form
]

<SynDictEntry> :: = [
    [synonym*],             // list of synonyms
    word_id                 // string to identify the word, used also in DefDict and ExapleDict
]

<DefDict> ::= [             // Dictionary that contains Definitions of the source word
    pos_name,               // can be empty
    [<DefDictEntry>*],
    word_base_form
]

<DefDictEntry> ::= [
    definition,
    word_id,
    definition_example_usage
]

<ExampleDict> ::= [         // Dictionary that contains usage Examples of the source word
    [<ExampleDictEntry>*]
]

<ExampleDictEntry> ::= [
    example,
    ?,
    ?,
    ?,
    ?-num,
    word_id
]

<SeeAlsoDict> ::= [
    [SeeAlso*]              // list of suggestions to see
]

<PosDictEnum> ::=          // an enum of possible part-of-speech for PosDict
    1 |     // Noun
    2 |     // Verb
    3 |     // Adjective
    5 |     // Preposition
    6 |     // Abbreviation
    7 |     // Conjunction
    8 |     // Pronoun
    9 |     // Interjection
   10       // Phrase


/////////////////////////////////////////////////
// Example relpy:

[
    [
        ["Bonjour","Hello"]
    ],

    [
        [
            "interjection",
            ["Bonjour!","Salut!","Tiens!","Allô!"],
            [
                [
                    "Bonjour!",
                    ["Hello!","Hi!","Good morning!","Good afternoon!","Welcome!","How do you do?"],
                    ,
                    0.7548396
                ],
                [
                    "Salut!",
                    ["Hi!","Hello!","Salute!","All the best!","Hallo!","Hullo!"],
                    ,
                    0.032144949
                ],
                [
                    "Tiens!",
                    ["Hallo!","Hello!","Hullo!","Why!"]
                ],
                [
                    "Allô!",
                    ["Hello!","Hullo!","Hallo!"]
                ]
            ],
            "Hello!",
            9
        ]
    ],
    "en",
    ,
    [["Bonjour",[1],true,false,1000,0,1,0]],
    [["Hello",1,[["Bonjour",1000,true,false]],[[0,5]],"Hello",0,1]]
    ,
    ,
    ,
    [["en"],,[0.63999999]]
    ,
    ,
    ,
    [
        [
            "noun",
            [[["howdy","hullo","hi","how-do-you-do"],""]],
            "hello"
        ],
        [
            "exclamation",
            [[["hi","howdy","hey","hiya","ciao","aloha"],"m_en_us1254307.001"]],
            "hello"
        ]
    ],
    [
        [
            "noun",
            [["an utterance of “hello”; a greeting.","m_en_us1254307.006","she was getting polite nods and hellos from people"]],
            "hello"
        ],
        [
            "exclamation",[["used as a greeting or to begin a telephone conversation.","m_en_us1254307.001","hello there, Katie!"]],
            "hello"
        ],
        [   "verb",
            [["say or shout “hello”; greet someone.","m_en_us1254307.007","‘Hi Kirsten,’ he helloed , obviously calling me Kirsten on purpose."]],
            "hello"
        ]
    ],
    ,
    [["hello"]]
]