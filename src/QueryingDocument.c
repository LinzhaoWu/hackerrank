#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

typedef struct document document;
typedef struct paragraph paragraph;
typedef struct sentence sentence;
typedef struct word word;

struct document get_document(char* text) {
    document retDoc;
    char* arrParas[MAX_PARAGRAPHS] = {0};

    // For paragraphs
    const char* newlineDelimiters = "\n";
    const char* sentenceDelimiters = ".";
    const char* wordDelimiters = " ";

    char* sParaTok = strtok(text, newlineDelimiters);
    int iPara = 0;
    while (sParaTok) {
        arrParas[iPara++] = sParaTok;
        sParaTok = strtok(NULL, newlineDelimiters);
    }
    retDoc.paragraph_count = iPara;
    retDoc.data = (paragraph*)malloc(retDoc.paragraph_count * sizeof(paragraph));

    // For sentences
    for (int i = 0; i < iPara; i++) {
        char* sSentTok = strtok(arrParas[i], sentenceDelimiters);
        int iSentences = 0;
        char* arrSentences[MAX_CHARACTERS / 2] = {0};
        while (sSentTok) {
            arrSentences[iSentences++] = sSentTok;
            sSentTok = strtok(NULL, sentenceDelimiters);
        }
        retDoc.data[i].sentence_count = iSentences;
        retDoc.data[i].data = (sentence*)malloc(retDoc.data[i].sentence_count * sizeof(sentence));

        for (int j = 0; j < iSentences; j++) {
            char* sWordTok = strtok(arrSentences[j], wordDelimiters);
            int iWords = 0;
            char* arrWords[MAX_CHARACTERS / 2] = {0};
            while (sWordTok)
            {
                arrWords[iWords++] = sWordTok;
                sWordTok = strtok(NULL, wordDelimiters);
            }
            retDoc.data[i].data[j].word_count = iWords;
            retDoc.data[i].data[j].data = (word*)malloc(retDoc.data[i].data[j].word_count * sizeof(word));
            for (int k = 0; k < iWords; k++) {
                retDoc.data[i].data[j].data[k].data = arrWords[k];
            }
        }
    }
    return retDoc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}