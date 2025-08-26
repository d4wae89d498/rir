static void interpret_call(IRNode *self) {
    // ffi stuff
}

IRVisitor interpret_visitor() {
    IRVisitor output = .. ;

    IRVisitor_set("Call", interpret_call);


    return output;
}