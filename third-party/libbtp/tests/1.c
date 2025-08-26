#include "../btp.h"
#include <stdio.h>
#include <string.h>

/* ================================
   User-defined parser context data
   ================================ */
typedef struct {
    int rule_hits;
} MyUserData;

/* Declare a parser type named Parser_MyLang
   with user_data type = MyUserData */
BTP_DECLARE_PARSER(Parser_MyLang, MyUserData)

/* Simple grammar rules */
bool rule_hello(Parser_MyLang *p) {
    if (btp_token(p, "hello")) {
        p->user_data->rule_hits++;
        return true;
    }
    return false;
}

bool rule_world(Parser_MyLang *p) {
    if (btp_token(p, "world")) {
        p->user_data->rule_hits++;
        return true;
    }
    return false;
}

/* Example composite rule */
bool rule_hello_world(Parser_MyLang *p) {
    return btp_sequence(p, rule_hello, rule_world, NULL);
}

int main(void) {
    const char *input = "helloworld";

    MyUserData ctx = {0};
    Parser_MyLang parser;
    btp_init(&parser, input, strlen(input), &ctx);

    if (rule_hello_world(&parser)) {
        printf("Parse OK. Hits = %d\n", ctx.rule_hits);
    } else {
        printf("Parse error at %u:%u: %s\n",
               parser.error_line, parser.error_column,
               parser.error_msg ? parser.error_msg : "(no message)");
    }

    return 0;
}
