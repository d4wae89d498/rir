#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include <btp.h>
#include <rir.h>


typedef struct {

} RirParserUserData;

BTP_DECLARE_PARSER(RirParser, RirParserUserData)

///////////////////////////////////////////

bool identifier(Parser *ps) 
{
	RirParser *p = (RirParser*) ps;
	if (isalpha(p->input[p->pos]) || p->input[p->pos] == '_') {
		size_t start = p->pos;
		p->pos += 1;
		while (isalnum(p->input[p->pos]) || p->input[p->pos] == '_')
			p->pos += 1;
		btp_push_val(p, strndup(p->input + start, p->pos - start));
	}
	return false;
}


bool parse_binop(RirParser *p) {

	if (btp_rule(p, identifier)
	&& (
		btp_token(p, "+")
		|| btp_token(p, "-")
		|| btp_token(p, "*")
		|| btp_token(p, "/")
		|| btp_token(p, "%")
	)
	&& btp_rule(p, identifier)) {

		char *op = stack_pop(p->value_stack, &p->value_stack_len);

		if (op == plus) {
			binop *o = binop_add(NULL, NULL, NULL);
			o->dest = temp(ctx, "");
			o->left = hmap_find(ctx, "...");
			temp_uses(o->left, o);
			o->right = hmap_find(ctx, "...");
			temp_uses(o->right, o);

			btp_push_val(p, )
		} else if (op == mult) {

		} else if (op == div) {

		}
	}

}

bool assignement(RirParser *p) {
	return btp_optional(p, space)
	&& btp_rule(p, identifier)
	&& btp_optional(p, space)
	&& btp_match_str(p, "=")
	&& btp_optional(p, space)
	&& btp_choice(p, binop, unaryop, identifier)
	&& btp_rule(p, instr_end);

}

bool rir_parse_statement(RirParser *p) {
	return btp_choice(p,
		assignement,
		comparaison,
		jump
	)
}

bool rir_parse_program_step(RirParser *p) {

}

bool rir_parse_program(RirParser *p) {
	while (p->input[p->pos]) {
		size_t step_pos = p->pos;

		if (!rir_parse_program_step(p))
		{
			// error
			p->pos += 1; // continue parsing.. increment error count etc..
				     // use longest matchng one for the keep it as error one
		} else if (step_pos == p->pos) {
			// error : a rule was accepted without consuming a character ...
		}
	}
}
