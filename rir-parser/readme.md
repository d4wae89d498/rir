# RIR-PARSER SECIFICATION

```B

// will merge meta structs
meta import ...

// wont merge meta structs
import * from "foo/bar.bpp"
import {foo} from ""
import {foo} as P from ""
import * as P from ""


meta {

}

f() {

}

export main(ac, av) {

    extern printf

    static i

    buff[256]

    tmp1 = 9 + 32 + 90

    if tmp1 {
        tmp1 = tmp1 + 2
    } else {
        printf("test %d", 12); tmp1++;
    }

    for i = 0; i < 5; i++ {
        buf[0] = 0
    }

    while i < 5 {
        i ++;
    }

    

    return 0
}

```

- ++i i++ / --i / i-- 
- i += *= ...

(all classic C operators)

- typeless (everything is a word by default)

- extern to refer address to be linked

- optional semicolons, no parentheses for controls structs