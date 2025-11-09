#ifndef RIR_WHEN_H
# define RIR_WHEN_H
# include <rir.h>

struct  when {
    terminator  terminator;
    value       *cond;
    block       *t;
    block       *f;
};

visitable(node_visitor, node, when, self)

static when *when_new(value *cond, block *t, block *f) {
    return new(when, 
        .terminator = terminator_impl(
            .accept = (node_method) &when_visit,
            .type = "when",
        ),
        .cond = cond,
        .t = t,
        .f = f
    );
}

//////////////////////////////
// When Builder

typedef struct when_frame {
    block *true_branch;
    block *false_branch;
    block *finally_branch;
} when_frame;

# define T when_frame_stack, when_frame
# include <stc/stack.h>

static when_frame_stack when_frames;
static bool when_frames_initied = false;

static when* When(value *cond) {

    if (!when_frames_initied) {
        when_frames = when_frame_stack_init();
        when_frames_initied = true;
    }

    when_frame frame;
    frame.true_branch = block_new(block_id++);
    frame.false_branch = block_new(block_id++);
    frame.finally_branch = block_new(block_id++);

    when_frame_stack_push(&when_frames, frame);

    when *self = when_new(cond, frame.true_branch, frame.false_branch);
    builder_attach_instr(&self->terminator.instr);

    builder_begin_block(frame.true_branch);

    return self;
}

# define otherwise \
    if (1) { \
        const when_frame *frame = when_frame_stack_top(&when_frames); \
        jump(frame->finally_branch); \
        builder_begin_block(frame->false_branch); \
    }

# define endwhen \
    if (1) { \
        const when_frame *frame = when_frame_stack_top(&when_frames); \
        builder_begin_block(frame->finally_branch); \
        when_frame_stack_pop(&when_frames); \
    }

# define when(a) When(a);

#endif // RIR_WHEN_H