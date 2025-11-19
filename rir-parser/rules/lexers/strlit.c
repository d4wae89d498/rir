#include <rir.h>

// === strlit ===
static int strlit_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    const char *input = std_parser_ctx->src;
    if (input[0] != '"')
        return -1;
    
    // Allocate output buffer (worst case: no escapes, same length as input minus quotes)
    char* output = malloc(255);
    if (output == NULL) {
        error("Allocation error");
        exit(1);
    }
    
    size_t in_index = 1;  // Skip opening quote
    size_t out_index = 0;
    
    while (input[in_index] != '\"') {  // Stop before closing quote
        if (!input[in_index]) {
                error("Unterminated strlit");
                free(output);
                return -1;
        }
        if (input[in_index] == '\\') {
            in_index++;  // Skip backslash
            


            if (input[in_index] == '\"' || !input[in_index]) {
                error("Invalid escape at end of stringlit");
                free(output);
                return -1;
            }
            
            switch (input[in_index]) {
                case 'a': output[out_index++] = '\a'; break;
                case 'b': output[out_index++] = '\b'; break;
                case 'f': output[out_index++] = '\f'; break;
                case 'n': output[out_index++] = '\n'; break;
                case 'r': output[out_index++] = '\r'; break;
                case 't': output[out_index++] = '\t'; break;
                case 'v': output[out_index++] = '\v'; break;
                case '\\': output[out_index++] = '\\'; break;
                case '"': output[out_index++] = '"'; break;
                case '\'': output[out_index++] = '\''; break;
                case '?': output[out_index++] = '?'; break;
                
                case 'x': {
                    in_index++;  // Skip 'x'
                    if ((input[in_index] == '\"' || !input[in_index]) || !isxdigit(input[in_index])) {
                        error("Invalid \\x escape: expected a xdigit, got %c [%d]", input[in_index], !isxdigit(input[in_index]));
                        free(output);
                        return -1;
                    }
                    
                    char hex[3] = {0};
                    int hex_len = 0;
                    
                    // Read up to 2 hex digits
                    while (!(input[in_index] == '\"' || !input[in_index]) && isxdigit(input[in_index]) && hex_len < 2) {
                        hex[hex_len++] = input[in_index++];
                    }
                    
                    char* endptr;
                    long value = strtol(hex, &endptr, 16);
                    if (endptr == hex) {  
                        error("No digits converted for [%.3s]", hex);
                        free(output);
                        return -1;
                    }
                    
                    output[out_index++] = (char)value;
                    in_index--;
                    break;
                }
                
                default:
                    if (input[in_index] >= '0' && input[in_index] <= '7') {
                        char octal[4] = {0};
                        int octal_len = 0;
                        
                        // up to 3 octal digits
                        while (!(input[in_index] == '\"' || !input[in_index]) && 
                               input[in_index] >= '0' && 
                               input[in_index] <= '7' && 
                               octal_len < 3) {
                            octal[octal_len++] = input[in_index++];
                        }
            
                        char* endptr;
                        long value = strtol(octal, &endptr, 8);
                        if (endptr == octal) {
                            error("No digits converted for [%.4s]", octal);
                            free(output);
                            return -1;
                        }
                        
                        output[out_index++] = (char)value;
                        in_index--;
                    } else {
                        error("Invalid escape sequence");
                        free(output);
                        return -1;
                    }
                    break;
            }
        } else {
            output[out_index++] = input[in_index];
        }
        
        in_index++;
    }
    output[out_index] = 0;
    
    const char *str = strndup(input, in_index + 1);

    debug("parsed[%s] from [%s]\n", output,  str);
    
    value *pushme = value_new(temp_id++, &strlit_new(
        str
    )->expr);

    // todo: pushme

    
    return out_index + 2;
}

bpc_parser *strlit_parser = &strlit_parser_impl;
