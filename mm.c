/**
 * @file mm.c
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @brief a 64-bit struct-based segregated free list dynamic memory allocator
 *
 * 15-213: Introduction to Computer Systems
 * 
 * the segregated free list implementation uses 12 free list classes, with
 *  byte demarcations of {32, 48, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}
<<<<<<< HEAD
=======
=======
 * @brief a 64-bit struct-based segregated free list memory allocator
 *
 * 15-213: Introduction to Computer Systems
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
 * 
 * the segregated free list implementation uses 12 free list classes, with
 *  class demarcations of {32, 48, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * additionally, the free lists follow a LIFO addition policy
 * 
 * internally, each free list is doubly-linked and follows an invariant of 
 *  terminating NULL pointers, so the first blocks prev pointer and the last 
 *  block's next pointer are both NULL
 * 
<<<<<<< HEAD
 * to decrease internal fragmentation, the minimum block size is set to 16-bytes
 * 
 * there is an additional free list class with size 16-byte blocks that
 *  manages blocks that are too small for the normal free list classes.
 *  This list is singly linked, where blocks encompass only a header and next pointer
 * 
 * additionally, footers are removed from allocated blocks to increase
 *  the memory utilization and decrease internal fragmentation
 * 
 * the fit algorithm is 'better fit' which first finds a suitable block,
 *  then does a bounded search for a better fit than the first available block
 * 
=======
<<<<<<< HEAD
 * additionally, footers are removed from allocated blocks to increase
 *  the memory utilization and decrease internal fragmentation
 * 
=======
<<<<<<< HEAD
=======
=======
 *
<<<<<<< HEAD
 * basic explicit list dynamic memory allocator with LIFO, FIFO free block 
 *  placement policies (placing at beginning or end of explicit free list)
 * 
 * the memory allocator maintains an internal doubly-linked free list
 *  with terminal NULL pointers and list_root, list_tail pointers
 * 
 * the memory utilization performance of 59.6% was achieved with a LIFO
 *  placement policy using add_to_free_list_tail() with first_fit search
=======
 * basic explicit list dynamic memory allocator with LIFO free block placement
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
 *
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 *************************************************************************
 *
 * ADVICE FOR STUDENTS.
 * - Step 0: Please read the writeup!
 * - Step 1: Write your heap checker.
 * - Step 2: Write contracts / debugging assert statements.
 * - Good luck, and have fun!
 *
 *************************************************************************
 *
 * @author Chetan Chilkunda <cchilkun@andrew.cmu.edu>
 */

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* Do not change the following! */

#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#define memset mem_memset
#define memcpy mem_memcpy
#endif /* def DRIVER */

/* You can change anything from here onward */

/*
 *****************************************************************************
 * If DEBUG is defined (such as when running mdriver-dbg), these macros      *
 * are enabled. You can use them to print debugging output and to check      *
 * contracts only in debug mode.                                             *
 *                                                                           *
 * Only debugging macros with names beginning "dbg_" are allowed.            *
 * You may not define any other macros having arguments.                     *
 *****************************************************************************
 */
#ifdef DEBUG
/* When DEBUG is defined, these form aliases to useful functions */
#define dbg_requires(expr) assert(expr)
#define dbg_assert(expr) assert(expr)
#define dbg_ensures(expr) assert(expr)
#define dbg_printf(...) ((void)printf(__VA_ARGS__))
#define dbg_printheap(...) print_heap(__VA_ARGS__)
#else
/* When DEBUG is not defined, these should emit no code whatsoever,
 * not even from evaluation of argument expressions.  However,
 * argument expressions should still be syntax-checked and should
 * count as uses of any variables involved.  This used to use a
 * straightforward hack involving sizeof(), but that can sometimes
 * provoke warnings about misuse of sizeof().  I _hope_ that this
 * newer, less straightforward hack will be more robust.
 * Hat tip to Stack Overflow poster chqrlie (see
 * https://stackoverflow.com/questions/72647780).
 */
#define dbg_discard_expr_(...) ((void)((0) && printf(__VA_ARGS__)))
#define dbg_requires(expr) dbg_discard_expr_("%d", !(expr))
#define dbg_assert(expr) dbg_discard_expr_("%d", !(expr))
#define dbg_ensures(expr) dbg_discard_expr_("%d", !(expr))
#define dbg_printf(...) dbg_discard_expr_(__VA_ARGS__)
#define dbg_printheap(...) ((void)((0) && print_heap(__VA_ARGS__)))
#endif

/* Basic constants */

typedef uint64_t word_t;

/** @brief Word and header size (bytes) */
static const size_t wsize = sizeof(word_t);

/** @brief Double word size (bytes) */
static const size_t dsize = 2 * wsize;

/** @brief Minimum block size (bytes) */
static const size_t min_block_size = dsize;

/** @brief Heap extension size (heap chunks) (Must be divisible by dsize) */
static const size_t chunksize = (1 << 12);

<<<<<<< HEAD
/** @brief alloc_mask used when marking each block as either free or malloc'd */
=======
<<<<<<< HEAD
/** @brief alloc_mask used when marking each block as either free or malloc'd */
=======
/**
<<<<<<< HEAD
 * @brief alloc_mask is used when marking each block as either 
=======
<<<<<<< HEAD
 * @brief alloc_mask is used when marking each block as either 
=======
<<<<<<< HEAD
 * @brief alloc_mask is used when marking each block as either 
=======
<<<<<<< HEAD
 * @brief alloc_mask is used when marking each block as either 
=======
<<<<<<< HEAD
 * @brief alloc_mask is used when marking each block as either 
=======
 * alloc_mask is used when marking each block as either 
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
 *  free or malloc'd (this is used in the header)
 *  NOTE: the header is defined as the size of the block | alloc flag
 */
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
static const word_t alloc_mask = 0x1;

/** @brief prev_alloc_mask used to mark previous block's allocation status */
static const word_t prev_alloc_mask = 0x2;

<<<<<<< HEAD
/** @brief prev_mini_mask used to mark whether previous block is a mini block */
static const word_t prev_mini_mask = 0x4;

/**
=======
/**
<<<<<<< HEAD
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @brief size_mask takes advantage of the fact that the low bits are zero,
 *  so gets everything except the lower order bits (as blocks are 16-byte aligned)
 */
static const word_t size_mask = ~(word_t)0xF;

<<<<<<< HEAD
/** @brief Total number of segregated free lists (including mini block list) */
#define NUM_LISTS 13

/** @brief Represents the header and payload of one block in the heap */
typedef struct block {
    /** @brief header contains size + prev_mini + prev_alloc + alloc flags */
    word_t header;

    /** @brief union of the payload memory space, used either for
     *  the payload itself, the prev, next pointers in the free lists,
     *  or for the next pointers in the mini block free list */
    union payload_space {
        struct block *next_mini;
        struct block *p[2];
        char payload[0];
    } space;

=======
/** @brief Total number of segregated free lists */
#define NUM_LISTS 12

/** @brief Represents the header and payload of one block in the heap */
typedef struct block {
    /** @brief header contains size + prev_alloc + alloc flags */
    word_t header;

    /** @brief union of the payload memory space, used either for
     *  the payload itself or the prev, next pointers in the free lists */
=======
<<<<<<< HEAD
 * @brief size_mask is used to force the low bits to be zero, to hold possibly
=======
<<<<<<< HEAD
 * @brief size_mask is used to force the low bits to be zero, to hold possibly
=======
<<<<<<< HEAD
 * @brief size_mask is used to force the low bits to be zero, to hold possibly
=======
<<<<<<< HEAD
 * @brief size_mask is used to force the low bits to be zero, to hold possibly
=======
<<<<<<< HEAD
 * @brief size_mask is used to force the low bits to be zero, to hold possibly
=======
 * TODO: size_mask is used to force the low bits to be zero, to hold possibly
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
 *  the boolean flag of free / malloc'd and the previous block malloc'd flag
 */
static const word_t size_mask = ~(word_t)0xF;

<<<<<<< HEAD
/** @brief Total number of segregated free lists */
#define NUM_LISTS 12
=======
<<<<<<< HEAD
/** @brief Total number of segregated free lists */
#define NUM_LISTS 12
=======
/** @brief tracks the length of the explicit free list */
static size_t free_list_length = 0;
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e

/** @brief Represents the header and payload of one block in the heap */
typedef struct block {
    /** @brief Header contains size + allocation flag + prev allocation flag */
    word_t header;

    /** @brief union of the payload memory space, used either for
<<<<<<< HEAD
     *  the payload itself or the prev, next pointers in the free lists
=======
<<<<<<< HEAD
     *  the payload itself or the prev, next pointers in the free lists
=======
     *  the payload itself or the prev, next pointers in the explicit free list
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
     */
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
    union payload_space {
        struct block *p[2];
        char payload[0];
    } space;

>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
} block_t;

/* Global variables */

/** @brief Pointer to first block in the heap */
static block_t *heap_start = NULL;

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
/** @brief Array of free lists (marked by its root pointer) */
static block_t *seg_list_array[NUM_LISTS];

/** @brief total number of free blocks in segregated list array */
static size_t free_block_count = 0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
static void print_block(block_t *bp);
static void print_heap(void);

=======
<<<<<<< HEAD
=======
=======
/** @brief Pointer to first free block in explicit list */
static block_t *free_list_root = NULL;

<<<<<<< HEAD
/** @brief Pointer to last free block in explicit list */
static block_t *free_list_tail = NULL;

=======
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
/*
 *****************************************************************************
 * The functions below are short wrapper functions to perform                *
 * bit manipulation, pointer arithmetic, and other helper operations.        *
 *                                                                           *
 * We've given you the function header comments for the functions below      *
 * to help you understand how this baseline code works.                      *
 *                                                                           *
 * Note that these function header comments are short since the functions    *
 * they are describing are short as well; you will need to provide           *
 * adequate details for the functions that you write yourself!               *
 *****************************************************************************
 */

/*
 * ---------------------------------------------------------------------------
 *                        BEGIN SHORT HELPER FUNCTIONS
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Returns the maximum of two integers.
 * @param[in] x
 * @param[in] y
 * @return `x` if `x > y`, and `y` otherwise.
 */
static size_t max(size_t x, size_t y) { return (x > y) ? x : y; }

/**
 * @brief Rounds `size` up to next multiple of n
 * @param[in] size
 * @param[in] n
 * @return The size after rounding up
 */
static size_t round_up(size_t size, size_t n) {
    return max(n * ((size + (n - 1)) / n), min_block_size);
}

/**
<<<<<<< HEAD
 * @brief Packs the block's 'size', 'prev_alloc', 'alloc', and 'prev_mini' flags
=======
<<<<<<< HEAD
 * @brief Packs the block's 'size' and 'alloc' flags
=======
 * @brief Packs the block's 'size' and 'alloc' flag
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 *        into a word suitable for use as a packed value.
 *
 * Packed values are used for both headers and free block footers.
 * 
 * The allocation status is packed into the lowest bit of the word.
 * 
 * The previous block's allocation status packed into second lowest bit of word.
<<<<<<< HEAD
 * 
 * The previous block's mini status packed into third lowest bit of word.
 *
 * @param[in] size The size of the block being represented
 * @param[in] prev_mini True if the previous block is a mini block
=======
 *
 * @param[in] size The size of the block being represented
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @param[in] prev_alloc True if the previous block is allocated
 * @param[in] alloc True if the block is allocated
 * @return The packed value
 */
<<<<<<< HEAD
static word_t pack(size_t size, bool prev_mini, bool prev_alloc, bool alloc) {
    word_t word = size;
    if (prev_mini) {word |= prev_mini_mask; }
    if (prev_alloc) { word |= prev_alloc_mask; }
=======
static word_t pack(size_t size, bool prev_alloc, bool alloc) {
    word_t word = size;
<<<<<<< HEAD
    if (prev_alloc) { word |= prev_alloc_mask; }
=======
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    if (alloc) { word |= alloc_mask; }
    return word;
}

/**
 * @brief Extracts the size represented in a packed word.
 *
 * This function simply clears the lowest 4 bits of the word, as the heap
 * is 16-byte aligned.
 *
 * @param[in] word
 * @return The size of the block represented by the word
 */
static size_t extract_size(word_t word) { return (word & size_mask); }

/**
 * @brief Extracts the size of a block from its header.
 * @param[in] block
 * @return The size of the block
 */
static size_t get_size(block_t *block) { return extract_size(block->header); }

/**
 * @brief Given a payload pointer, returns a pointer to the corresponding
 *        block.
 * @param[in] bp A pointer to a block's payload
 * @return The corresponding block
 */
static block_t *payload_to_header(void *bp) {
    return (block_t *)((char *)bp - offsetof(block_t, space.payload));
}

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        payload.
 * @param[in] block
 * @return A pointer to the block's payload
 * @pre The block must be a valid block, not a boundary tag.
 */
static void *header_to_payload(block_t *block) {
    dbg_requires(get_size(block) != 0);
    return (void *)(block->space.payload);
}

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        footer.
 * @param[in] block
 * @return A pointer to the block's footer
 * @pre The block must be a valid block, not a boundary tag.
 */
static word_t *header_to_footer(block_t *block) {
    dbg_requires(get_size(block) != 0 &&
                 "Called header_to_footer on the epilogue block");
    return (word_t *)(block->space.payload + get_size(block) - dsize);
}

/**
 * @brief Given a block footer, returns a pointer to the corresponding
 *        header.
 * @param[in] footer A pointer to the block's footer
 * @return A pointer to the start of the block
 * @pre The footer must be the footer of a valid block, not a boundary tag.
 */
static block_t *footer_to_header(word_t *footer) {
    size_t size = extract_size(*footer);
    if (size == 0){
        return (block_t *)footer;
    }
    return (block_t *)((char *)footer + wsize - size);
}

/**
 * @brief Returns the allocation status of a given header value.
 *
 * This is based on the lowest bit of the header value.
 *
 * @param[in] word
 * @return The allocation status correpsonding to the word
 */
static bool extract_alloc(word_t word) {
    return (bool)(word & alloc_mask);
}

/**
 * @brief Returns the allocation status of a block, based on its header.
 * @param[in] block
 * @return The allocation status of the block
 */
static bool get_alloc(block_t *block) {
    return extract_alloc(block->header);
}

/**
 * @brief Returns the payload size of a given block.
 *
 * The payload size is equal to the entire block size minus the size of the
 * block's header.
 *
 * @param[in] block
 * @return The size of the block's payload
 */
static size_t get_payload_size(block_t *block) {
    size_t asize = get_size(block);
    return asize - wsize;
}

/**
 * @brief Returns previous block's allocation status from given header value.
 * 
 * This is based on second lowest bit of the header value.
 * 
 * @param[in] word
 * @return The previous block's allocation status corresponding to word
 */
static bool extract_prev_alloc(word_t word) {
    return (bool)(word & prev_alloc_mask);
}

/**
 * @brief Returns previous block's allocation status, from current block header.
 * 
 * @param[in] block
 * @return The previous block's allocation status
 */
static bool get_prev_alloc(block_t *block) {
    return extract_prev_alloc(block->header);
}

/**
<<<<<<< HEAD
 * @brief Returns previous block mini block status, from given header value.
 * 
 * This is based on third lowest bit of the header value.
 * 
 * @param[in] word
 * @return The previous block's mini block status corresponding to word
 */
static bool extract_prev_mini(word_t word) {
    return (bool)(word & prev_mini_mask);
}

/**
 * @brief Returns previous block mini status, from current block header.
 * 
 * @param[in] block
 * @return The previous block's mini status
 */
static bool get_prev_mini(block_t *block) {
    return extract_prev_mini(block->header);
}

/**
 * @brief Writes an epilogue header at the given address.
 *
 * The epilogue header has size 0, and is marked as allocated.
 *  By default, write_epilogue occurs when the heap is extended so
 *  the prev_mini and prev_alloc flags of the epilogue start as false.
=======
 * @brief Writes an epilogue header at the given address.
 *
 * The epilogue header has size 0, and is marked as allocated.
<<<<<<< HEAD
 *  By default, write_epilogue occurs when the heap is extended so
 *  the prev_alloc flag of the epilogue starts as false.
=======
 * 
 * Only update the epilogue when the heap is extended, 
 *  so by default the previous block is marked as free.
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 *
 * @param[out] block The location to write the epilogue header
 */
static void write_epilogue(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires((char *)block == (char *)mem_heap_hi() - 7);
<<<<<<< HEAD
    block->header = pack(0, false, false, true);
=======
<<<<<<< HEAD
    block->header = pack(0, false, true);
=======
    block->header = pack(0, true);
}

/**
<<<<<<< HEAD
=======
 * @brief Writes a block starting at the given address.
 *
 * This function writes both a header and footer, where the location of the
 * footer is computed in relation to the header.
 *
 * @pre The block must be a valid block, not a boundary tag.
 * @pre Positive block size
 * @post The block must be a valid block, not a boundary tag.
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
 * @param[in] alloc The allocation status of the new block
 */
static void write_block(block_t *block, size_t size, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(size > 0);
    block->header = pack(size, alloc);
    word_t *footerp = header_to_footer(block);
    *footerp = pack(size, alloc);
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
}

/**
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
 * @brief Finds the next consecutive block on the heap.
 *
 * This function accesses the next block in the "implicit list" of the heap
 * by adding the size of the block.
 *
 * @param[in] block A block in the heap
 * @return The next consecutive block on the heap
 * @pre The block is not the epilogue
 */
static block_t *find_next(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) != 0 &&
                 "Called find_next on the last block in the heap");
    return (block_t *)((char *)block + get_size(block));
}

/**
 * @brief Finds the footer of the previous block on the heap.
 * @param[in] block A block in the heap
 * @return The location of the previous block's footer
 */
static word_t *find_prev_footer(block_t *block) {
    // Compute previous footer position as one word before the header
    return &(block->header) - 1;
}

/** @brief Finds the previous mini block's header on the heap */
static block_t *find_prev_mini(block_t *block) {
    // Compute previous footer position as two words before the header
    return (block_t *)(&(block->header) - 2);
}

/**
 * @brief Finds the previous consecutive block on the heap.
 *
 * This is the previous block in the "implicit list" of the heap.
 *
 * The position of the previous block is found by reading the previous
 * block's footer to determine its size, then calculating the start of the
 * previous block based on its size.
 *
 * @param[in] block A block in the heap
 * @return The previous consecutive block in the heap.
 */
static block_t *find_prev(block_t *block) {
    dbg_requires(block != NULL);
<<<<<<< HEAD

    if (get_prev_mini(block)) {
        return find_prev_mini(block);
    } else {
        word_t *footerp = find_prev_footer(block);
        return footer_to_header(footerp);
    }
}

/**
 * @brief Writes a block starting at the given address.
 *
 * This function writes a header for allocated blocks and mini blocks
 *  and both a header and footer for free blocks, where the location of 
 *  the footer is computed in relation to the header.
 *
 * @pre The block must be a valid block, not a boundary tag.
 * @pre Positive block size
 * @post The block must be a valid block, not a boundary tag.
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
 * @param[in] prev_mini The previous block's mini status
 * @param[in] prev_alloc The previous block's allocation status
 * @param[in] alloc The allocation status of the new block
 */
static void write_block(block_t *block, size_t size, bool prev_mini, bool prev_alloc, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(size > 0);

    block->header = pack(size, prev_mini, prev_alloc, alloc);

    if (!alloc && size >= 2 * dsize) { // writing free block footer
        word_t *footerp = header_to_footer(block);
        *footerp = pack(size, prev_mini, prev_alloc, alloc);
    }
}

/**
 * @brief Updates the subsequent block's prev_mini and prev_alloc flags
 * 
 * @param[in] block the current written block
 * @param[in] mini the mini block status of the current block
 * @param[in] alloc the allocation status of the current block
 */
static void update_next_block_header(block_t *block, bool mini, bool alloc) {
    block_t *next = find_next(block);
    next->header = pack(get_size(next), mini, alloc, get_alloc(next));

    if (get_size(next) >= 2 * dsize && !get_alloc(next)) { // writing free block footer
        word_t *next_footerp = header_to_footer(next);
        *next_footerp = pack(get_size(next), mini, alloc, get_alloc(next));
    }
=======
    word_t *footerp = find_prev_footer(block);
    return footer_to_header(footerp);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
}

/**
 * @brief Writes a block starting at the given address.
 *
 * This function writes both a header and footer, where the location of the
 * footer is computed in relation to the header.
 *
 * @pre The block must be a valid block, not a boundary tag.
 * @pre Positive block size
 * @post The block must be a valid block, not a boundary tag.
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
<<<<<<< HEAD
 * @param[in] prev_alloc The previous block's allocation status
 * @param[in] alloc The allocation status of the new block
 */
static void write_block(block_t *block, size_t size, bool prev_alloc, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(size > 0);

    block->header = pack(size, prev_alloc, alloc);

    if (!alloc) { // writing free block footer
        word_t *footerp = header_to_footer(block);
        *footerp = pack(size, prev_alloc, alloc);
    }
}

/**
 * @brief Updates the subsequent block's prev_alloc flag accordingly
 * 
 * @param[in] block the current written block
 * @param[in] alloc the allocation status of the current block
 */
static void update_next_block_header(block_t *block, bool alloc) {
    block_t *next = find_next(block);
    next->header = pack(get_size(next), alloc, get_alloc(next));

    if (get_size(next) != 0 && !get_alloc(next)) { // writing free block footer
        word_t *next_footerp = header_to_footer(next);
        *next_footerp = pack(get_size(next), alloc, get_alloc(next));
    }
=======
 * @param[in] alloc The allocation status of the new block
 */
static void write_block(block_t *block, size_t size, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(size > 0);

    block->header = pack(size, alloc);
    word_t *footerp = header_to_footer(block);
    *footerp = pack(size, alloc);
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
}

/*
 * ---------------------------------------------------------------------------
 *                        END SHORT HELPER FUNCTIONS
 * ---------------------------------------------------------------------------
 */

/********           BEGIN SELF-DEFINED HELPER FUNCTIONS             ********/

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
/** @brief gets the specific segregated list size class based on block size
 * 
 * @pre block_size is a valid block size
 * 
 * @param[in] block_size the size of the current block
 * @return the segregated free list array index matching the block's size class
 */
static int get_seg_list_index(size_t block_size) {
    dbg_requires(block_size > 0);

<<<<<<< HEAD
    /* defining segregation boundaries for the total 13 free list classes */
    size_t SEG_0 = 16;
=======
    /* defining segregation boundaries for the total 12 free list classes */
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    size_t SEG_1 = 32;
    size_t SEG_2 = 48;
    size_t SEG_3 = 64;
    size_t SEG_4 = 128;
    size_t SEG_5 = 256;
    size_t SEG_6 = 512;
    size_t SEG_7 = 1024;
    size_t SEG_8 = 2048;
    size_t SEG_9 = 4096;
    size_t SEG_10 = 8192;
    size_t SEG_11 = 16384;

<<<<<<< HEAD
    if (block_size <= SEG_0) return 0;
    else if (block_size <= SEG_1) return 1;
    else if (block_size <= SEG_2) return 2;
    else if (block_size <= SEG_3) return 3;
    else if (block_size <= SEG_4) return 4;
    else if (block_size <= SEG_5) return 5;
    else if (block_size <= SEG_6) return 6;
    else if (block_size <= SEG_7) return 7;
    else if (block_size <= SEG_8) return 8;
    else if (block_size <= SEG_9) return 9;
    else if (block_size <= SEG_10) return 10;
    else if (block_size <= SEG_11) return 11;
    return 12; // [2**14 + 1, 2**64]
=======
    if (block_size <= SEG_1) return 0;
    else if (block_size <= SEG_2) return 1;
    else if (block_size <= SEG_3) return 2;
    else if (block_size <= SEG_4) return 3;
    else if (block_size <= SEG_5) return 4;
    else if (block_size <= SEG_6) return 5;
    else if (block_size <= SEG_7) return 6;
    else if (block_size <= SEG_8) return 7;
    else if (block_size <= SEG_9) return 8;
    else if (block_size <= SEG_10) return 9;
    else if (block_size <= SEG_11) return 10;
    return 11; // [2**14 + 1, 2**64]
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
}

/** @brief adds free block (pointed by bp) to the specified free list class
 * 
 * @pre the block must be a valid block, not a boundary tag
 * @pre the free list class index is within bounds of the segregated list array
 * 
 * @param[in] bp the free block being added to the list
 * @param[in] i the segregated list index that maps to a particular size class
 */
static void add_to_free_list(block_t *bp, int i) {
    dbg_requires(!get_alloc(bp)); // block must be free

    block_t *list_root = seg_list_array[i];

<<<<<<< HEAD
    if (i == 0) { // adding a free mini block
        dbg_assert(get_size(bp) <= dsize);

        bp->space.next_mini = list_root;
        seg_list_array[i] = bp;
    } else { // adding a 32-byte or larger free block
        dbg_assert(get_size(bp) >= 2 * dsize);

        bp->space.p[0] = NULL;
        bp->space.p[1] = list_root;

        if (list_root != NULL) { list_root->space.p[0] = bp; }
        seg_list_array[i] = bp;
    }
=======
    bp->space.p[0] = NULL;
    bp->space.p[1] = list_root;

    if (list_root != NULL) { list_root->space.p[0] = bp; }
    seg_list_array[i] = bp;
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    free_block_count += 1;
}

/** @brief removes free block (bp) from the specified free list class
 * 
 * @pre the block must be a valid block, not a boundary tag
 * @pre the free list class index is within bounds of the segregated list array
 * 
 * @param[in] bp the free block being removed from the list
 * @param[in] i the segregated list index that maps to a particular size class
 */
static void remove_from_free_list(block_t *bp, int i) {
    dbg_requires(!get_alloc(bp)); // block must be free
    dbg_requires(free_block_count > 0);

    block_t *list_root = seg_list_array[i];
    dbg_assert(list_root != NULL);

<<<<<<< HEAD
    if (i == 0) { // removing a mini free block
        dbg_assert(get_size(bp) <= dsize);

        if (list_root == bp) { // bp (mini) at beginning of free list
            seg_list_array[i] = bp->space.next_mini;

        } else { // bp (mini) in middle or at end of free list
            dbg_assert(free_block_count > 1);

            for (block_t *tmp = list_root; tmp != NULL; tmp = tmp->space.next_mini) {

                if (tmp->space.next_mini == bp) {
                    tmp->space.next_mini = bp->space.next_mini;
                    break;
                }
            }
        }

    } else { // removing a 32-byte or larger free block
        dbg_assert(get_size(bp) >= 2 * dsize);

        if (list_root->space.p[0] == NULL && list_root->space.p[1] == NULL) {
            seg_list_array[i] = NULL; // single element in free list class
        } else {
            dbg_assert(free_block_count > 1);
            if (bp == list_root) { // bp at beginning of free list
                dbg_assert(bp->space.p[0] == NULL);

                (bp->space.p[1])->space.p[0] = bp->space.p[0];
                seg_list_array[i] = bp->space.p[1];

            } else if (bp->space.p[1] == NULL) { // bp at end of free list
                (bp->space.p[0])->space.p[1] = bp->space.p[1];

            } else { // bp in middle of free list
                (bp->space.p[0])->space.p[1] = bp->space.p[1];
                (bp->space.p[1])->space.p[0] = bp->space.p[0];
            }
        }
    }

=======
    if (list_root->space.p[0] == NULL && list_root->space.p[1] == NULL) {
        seg_list_array[i] = NULL; // single element in free list class
    } else {
        dbg_assert(free_block_count > 1);
        if (bp == list_root) { // bp at beginning of free list
            dbg_assert(bp->space.p[0] == NULL);

            (bp->space.p[1])->space.p[0] = bp->space.p[0];
            seg_list_array[i] = bp->space.p[1];

        } else if (bp->space.p[1] == NULL) { // bp at end of free list
            (bp->space.p[0])->space.p[1] = bp->space.p[1];
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
/** @brief adds free block (pointed by bp) to end of explicit free list
 * 
 * @pre The block must be a valid block, not a boundary tag.
 * 
 * @param[in] bp the free block being added to the list
*/
static void add_to_free_list_tail(block_t *bp) {
    dbg_requires(!get_alloc(bp)); // block must be free

    bp->space.p[0] = free_list_tail;
    bp->space.p[1] = NULL;

    if (free_list_tail == NULL) { free_list_root = bp; }
    else { free_list_tail->space.p[1] = bp; }
    free_list_tail = bp;

    free_list_length += 1;
}

=======
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
/** @brief adds free block (pointed by bp) to beginning of explicit free list
 * 
 * @pre The block must be a valid block, not a boundary tag.
 * 
 * @param[in] bp the free block being added to the list
*/
<<<<<<< HEAD
static void add_to_free_list_head(block_t *bp) {
=======
static void add_to_free_list(block_t *bp) {
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
    dbg_requires(!get_alloc(bp)); // block must be free

    bp->space.p[0] = NULL;
    bp->space.p[1] = free_list_root;

<<<<<<< HEAD
    if (free_list_root == NULL) { free_list_tail = bp; }
    else { free_list_root->space.p[0] = bp; }
=======
    if (free_list_root != NULL) { free_list_root->space.p[0] = bp; }
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
    free_list_root = bp;

    free_list_length += 1;
}

/** @brief removes free block (pointed by bp) from explicit free list
 * 
 * @pre The block must be a valid block, not a boundary tag.
 * 
 * @param[in] bp the free block being removed from the list
*/
static void remove_from_free_list(block_t *bp) {
    dbg_requires(!get_alloc(bp)); // block must be free
<<<<<<< HEAD
    dbg_requires(free_list_length > 0);
    dbg_requires(free_list_root != NULL && free_list_tail != NULL);

    if (free_list_length <= 1) {
        free_list_root = bp->space.p[1];
        free_list_tail = bp->space.p[0];
=======
<<<<<<< HEAD
    dbg_requires(free_list_root != NULL && free_list_length > 0);

    if (free_list_length <= 1) {
=======
    //dbg_requires(free_list_root != NULL && free_list_length > 0);

    if (free_list_length <= 1) {
        //dbg_assert(bp->space.p[1] == NULL);
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
        free_list_root = bp->space.p[1];
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
    } else {
        dbg_assert(free_list_length > 1);
        if (bp == free_list_root) { // bp at beginning of free list
            dbg_assert(bp->space.p[0] == NULL);

            (bp->space.p[1])->space.p[0] = bp->space.p[0];
            free_list_root = bp->space.p[1];

<<<<<<< HEAD
        } else if (bp == free_list_tail) { // bp at end of free list
            dbg_assert(bp->space.p[1] == NULL);
            (bp->space.p[0])->space.p[1] = bp->space.p[1];
            free_list_tail = bp->space.p[0];
=======
        } else if (bp->space.p[1] == NULL) { // bp at end of free list
            (bp->space.p[0])->space.p[1] = bp->space.p[1];
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd

        } else { // bp in middle of free list
            (bp->space.p[0])->space.p[1] = bp->space.p[1];
            (bp->space.p[1])->space.p[0] = bp->space.p[0];
        }
    }

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    free_block_count -= 1;
}

/** @brief wrapper function that adds block (bp) to its size class free list 
 * 
 * @pre the block must be a valid block, not a boundary tag
 * 
 * @param[in] bp free block being added to the segregated free list array
 */
static void add_to_seg_list(block_t *bp) {
<<<<<<< HEAD
    dbg_requires(!get_alloc(bp));

=======
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    int list_index = get_seg_list_index(get_size(bp));
    add_to_free_list(bp, list_index);
}

/** @brief wrapper function that removes block (bp) from its size class free list
 * 
 * @pre the block must be a valid block, not a boundary tag
 * 
 * @param[in] bp free block being removed from the segregated free list array
 */
static void remove_from_seg_list(block_t *bp) {
<<<<<<< HEAD
    dbg_requires(!get_alloc(bp));

    int list_index = get_seg_list_index(get_size(bp));
    remove_from_free_list(bp, list_index);
=======
    int list_index = get_seg_list_index(get_size(bp));
    remove_from_free_list(bp, list_index);
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
    free_list_length -= 1;
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
}

/********            END SELF-DEFINED HELPER FUNCTIONS              ********/

/******** The remaining content below are helper and debug routines ********/

/**
 * @brief Combines neighboring free blocks into a "coalesced", larger block
 *
 * @pre The block must be a valid block, not a boundary tag.
 * @post The block must be a valid block, not a boundary tag.
 *
 * @param[in] block (the current block being freed)
 * @return the "coalesced", larger block
 */
static block_t *coalesce_block(block_t *block) {
<<<<<<< HEAD
    block_t *next = find_next(block);
=======
<<<<<<< HEAD
    block_t *next = find_next(block);
=======

    block_t *prev = find_prev(block);
    block_t *next = find_next(block);

    size_t prev_size = get_size(prev);
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    size_t next_size = get_size(next);
    size_t block_size = get_size(block);

    // CASE #1: current (free) block sandwiched by allocated blocks
<<<<<<< HEAD
    if (get_prev_alloc(block) && get_alloc(next)) {
        write_block(block, block_size, get_prev_mini(block), true, false);
=======
<<<<<<< HEAD
    if (get_prev_alloc(block) && get_alloc(next)) {
        write_block(block, block_size, true, false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    } 
    // CASE #2: prev allocated block - curr (free) block - next free block
    else if (get_prev_alloc(block) && !get_alloc(next)) {
        remove_from_seg_list(next);
<<<<<<< HEAD
        write_block(block, block_size + next_size, get_prev_mini(block), true, false);
=======
        write_block(block, block_size + next_size, true, false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    }
    // CASE #3: prev free block, current (free) block, next allocated block
    else if (!get_prev_alloc(block) && get_alloc(next)) {
        dbg_assert(!get_alloc(find_prev(block)));

        block_t *prev = find_prev(block);
        size_t prev_size = get_size(prev);

        remove_from_seg_list(prev);
<<<<<<< HEAD
        write_block(prev, prev_size + block_size, get_prev_mini(prev), get_prev_alloc(prev), false);
=======
        write_block(prev, prev_size + block_size, get_prev_alloc(prev), false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
        block = prev;
    }
    // CASE #4: current (free) block sandwiched by free blocks
    else if (!get_prev_alloc(block) && !get_alloc(next)) {
        dbg_assert(!get_alloc(find_prev(block)));

        block_t *prev = find_prev(block);
        size_t prev_size = get_size(prev);

        remove_from_seg_list(prev);
        remove_from_seg_list(next);
<<<<<<< HEAD
        write_block(prev, prev_size + block_size + next_size, get_prev_mini(prev), get_prev_alloc(prev), false);
=======
        write_block(prev, prev_size + block_size + next_size, get_prev_alloc(prev), false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
        block = prev;
    }

    add_to_seg_list(block);
<<<<<<< HEAD

    bool mini_status = (get_size(block) <= dsize);
    update_next_block_header(block, mini_status, false);

=======
    update_next_block_header(block, false);

=======
    if (get_alloc(prev) && get_alloc(next)) {
        write_block(block, block_size, false);
    } 
    // CASE #2: prev allocated block - curr (free) block - next free block
    else if (get_alloc(prev) && !get_alloc(next)) {
<<<<<<< HEAD
        remove_from_seg_list(next);
=======
<<<<<<< HEAD
        remove_from_seg_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(next);
=======
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
        write_block(block, block_size + next_size, false);
    }
    // CASE #3: prev free block, current (free) block, next allocated block
    else if (!get_alloc(prev) && get_alloc(next)) {
<<<<<<< HEAD
        remove_from_seg_list(prev);
=======
<<<<<<< HEAD
        remove_from_seg_list(prev);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
=======
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
        write_block(prev, prev_size + block_size, false);
        block = prev;
    }
    // CASE #4: current (free) block sandwiched by free blocks
    else if (!get_alloc(prev) && !get_alloc(next)) {
<<<<<<< HEAD
        remove_from_seg_list(prev);
        remove_from_seg_list(next);
=======
<<<<<<< HEAD
        remove_from_seg_list(prev);
        remove_from_seg_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
        remove_from_free_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
        remove_from_free_list(next);
=======
<<<<<<< HEAD
        remove_from_free_list(prev);
        remove_from_free_list(next);
=======
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
        write_block(prev, prev_size + block_size + next_size, false);
        block = prev;
    }

<<<<<<< HEAD
    add_to_seg_list(block);

=======
<<<<<<< HEAD
    add_to_seg_list(block);

=======
<<<<<<< HEAD
    add_to_free_list_tail(block);

=======
<<<<<<< HEAD
    add_to_free_list(block);

=======
<<<<<<< HEAD
    add_to_free_list(block);

=======
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    return block;
}

/**
 * @brief Extends the filled heap by size bytes
 *
 * @param[in] size (the constant chunksize, defined above)
 * @return the extended free block or NULL if unsuccessful sbrk
 */
static block_t *extend_heap(size_t size) {
    void *bp;

    // Allocate an even number of words to maintain alignment
    size = round_up(size, dsize);
    if ((bp = mem_sbrk((intptr_t)size)) == (void *)-1) {
        return NULL;
    }

    /* writing new block one word before to overwrite previous epilogue */

    // Initialize free block header/footer
    block_t *block = payload_to_header(bp);

<<<<<<< HEAD
    write_block(block, size, get_prev_mini(block), get_prev_alloc(block), false);
=======
    write_block(block, size, get_prev_alloc(block), false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // Create new epilogue header
    block_t *block_next = find_next(block);
    write_epilogue(block_next);

<<<<<<< HEAD
    // Current extended space is not a mini block and is free, by design
    update_next_block_header(block, false, false);
=======
    update_next_block_header(block, false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // Coalesce in case the previous block was free
    block = coalesce_block(block);

    return block;
}

/**
<<<<<<< HEAD
 * @brief Tries to split a currently allocated block into a smaller
=======
 * @brief Splits a currently large allocated block into a smaller
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 *  allocated block followed by a free block to optimize memory utilization
 * 
 * @pre The block must be a valid block, not a boundary tag.
 *
<<<<<<< HEAD
 * @param[in] block the allocated block to be split
=======
 * @param[in] block the large, allocated block to be freed
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @param[in] asize the requested size of the malloc'd block
 */
static void split_block(block_t *block, size_t asize) {
    dbg_requires(get_alloc(block));
    dbg_requires(asize >= dsize);

    size_t block_size = get_size(block);
    bool mini_status = (asize <= dsize);

    if ((block_size - asize) >= min_block_size) { // not a perfect fit
        write_block(block, asize, get_prev_mini(block), get_prev_alloc(block), true);

<<<<<<< HEAD
        block_t *block_next;
        block_next = find_next(block);
        write_block(block_next, block_size - asize, mini_status, true, false);
        coalesce_block(block_next); // updating next-next block's header here
    }

    update_next_block_header(block, mini_status, true);
=======
    if ((block_size - asize) >= min_block_size) {
<<<<<<< HEAD
        write_block(block, asize, get_prev_alloc(block), true);

        block_t *block_next;
        block_next = find_next(block);
        write_block(block_next, block_size - asize, true, false);
=======
        write_block(block, asize, true);

        block_t *block_next;
        block_next = find_next(block);
        write_block(block_next, block_size - asize, false);
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
        coalesce_block(block_next);
    }

    update_next_block_header(block, true);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    dbg_ensures(get_alloc(block));
}

/**
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @brief iterates through the specific size class to find an 
 *  adaquetely sized free block that can hold the requested space
 *  if the current size class doesn't have any blocks, looks at successively
 *  larger classes until an adaquetely sized free block is found
<<<<<<< HEAD
 * 
 *  Once an adaquetely sized block is found, will perform bounded best fit
 *  on the subsequent k-many blocks to find the smallest block that satisfies
 *  the given size request.
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
 * @brief iterates through the explicit list to find an 
 *  adaquetely sized free block that can hold the requested space
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 *
 * @param[in] asize the adjusted size requested for allocation
 * @return a pointer to the adaquete block (found in the free list)
 */
static block_t *find_fit(size_t asize) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
    dbg_requires(asize >= min_block_size);

    block_t *block;
    for (int i = get_seg_list_index(asize); i < NUM_LISTS; i++) {
        dbg_assert(0 <= i && i <= NUM_LISTS);

        block = seg_list_array[i];

        while (block != NULL) {

<<<<<<< HEAD
            if (asize <= get_size(block)) { // found the first block

                int LIMIT = 15;
                block_t *best_block = block;

                // starting search at next block for a "better fit"
                if (i == 0) { block = block->space.next_mini; }
                else { block = block->space.p[1]; }

                // bounded best fit starting from the first block
                for (int count = 0; count < LIMIT && block != NULL; count++) {

                    if (asize <= get_size(block) && get_size(block) < get_size(best_block)) {
                        best_block = block;
                    }

                    if (i == 0) { block = block->space.next_mini; }
                    else { block = block->space.p[1]; }
                }

                return best_block;
            }

            if (i == 0) {
                dbg_assert(asize <= dsize);
                block = block->space.next_mini;
            } else {
                block = block->space.p[1];
            }
=======
            if (asize <= get_size(block)) { return block; }

            block = block->space.p[1];
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
        }
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524

    block_t *block = free_list_root;

    while (block != NULL) {
        if (asize <= get_size(block)) { return block; }

<<<<<<< HEAD
=======
=======
    block_t *block = free_list_root;

    while (block != NULL) {
        if (asize <= get_size(block)) { return block; }

>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
        block = block->space.p[1];
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
    }

    return NULL; // no fit found
}

/********           BEGIN SELF-DEFINED HEAP CHECK FUNCTIONS           ********/

<<<<<<< HEAD
/** @brief Checks invariants specific to "implicit list" heap representation */
static bool check_heap_block(block_t *bp) {
    // checking each block's address alignment
    dbg_assert((size_t)bp % 8 == (size_t)0);

    // checking block lies withing the heap boundaries
    block_t *prologue = mem_heap_lo();
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert((word_t)prologue < (word_t)bp && (word_t)bp < (word_t)epilogue);

    // checking minimum block size requirements
    word_t header = *(word_t *)bp;
    dbg_assert(extract_size(header) >= min_block_size);

    // checking free heap block invariants
    if (!get_alloc(bp) && get_size(bp) >= 2 * dsize) {
        // checking for matching header and footer values
        word_t footer = *header_to_footer(bp);
        dbg_assert(header == footer);

        // checking bit flag consistencies
        dbg_assert(extract_size(header) == extract_size(footer));
        dbg_assert(extract_prev_mini(header) == extract_prev_mini(footer));
        dbg_assert(extract_prev_alloc(header) == extract_prev_alloc(footer));
        dbg_assert(extract_alloc(header) == extract_alloc(footer));
    }

    // checking coalescing: no consecutive free blocks in heap
    dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));

    // checking second lowest bit flag maintains prev_alloc status
    dbg_assert(get_alloc(bp) == get_prev_alloc(find_next(bp)));

    // checking third lowest bit flag maintains prev_mini status
    size_t block_size = get_size(bp);
    dbg_assert((block_size <= dsize && get_prev_mini(find_next(bp)))
        || (block_size > dsize && !get_prev_mini(find_next(bp))));

    return true;
}

/** @brief Checking free block invariants specific to segregated free lists */
static bool check_free_block(block_t *bp) {
    // ensuring bit flags indicate free block
    dbg_assert(!get_alloc(bp) && !get_prev_alloc(find_next(bp)));

    // checking block lies withing the heap boundaries
    block_t *prologue = mem_heap_lo();
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert((word_t)prologue < (word_t)bp && (word_t)bp < (word_t)epilogue);

    if (get_size(bp) >= 2 * dsize) {
        // checking prev, next pointers are correctly linked
        if (bp->space.p[0] != NULL) {
            dbg_assert(bp->space.p[0]->space.p[1] == bp);
        }
        if (bp->space.p[1] != NULL) {
            dbg_assert(bp->space.p[1]->space.p[0] == bp);
        }
    }

    return true;
}

/** @brief Checking segregated free list block sizes match class demarcations */
static bool check_seg_list(block_t *list, int i) {
    /* defining segregation boundaries for the total 13 free list classes */
    size_t SEG_0 = 16;
    size_t SEG_1 = 32;
    size_t SEG_2 = 48;
    size_t SEG_3 = 64;
    size_t SEG_4 = 128;
    size_t SEG_5 = 256;
    size_t SEG_6 = 512;
    size_t SEG_7 = 1024;
    size_t SEG_8 = 2048;
    size_t SEG_9 = 4096;
    size_t SEG_10 = 8192;
    size_t SEG_11 = 16384;

    if (i == 0) {
        for (block_t *p = list; p != NULL; p = p->space.next_mini) {
            if (!(get_size(p) <= SEG_0)) { return false; }
        }
    } else if (i == 1) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_1)) { return false; }
        }
    } else if (i == 2) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_2)) { return false; }
        }
    } else if (i == 3) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_3)) { return false; }
        }
    } else if (i == 4) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_4)) { return false; }
        }
    } else if (i == 5) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_5)) { return false; }
        }
    } else if (i == 6) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_6)) { return false; }
        }
    } else if (i == 7) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_7)) { return false; }
        }
    } else if (i == 8) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_8)) { return false; }
        }
    } else if (i == 9) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_9)) { return false; }
        }
    } else if (i == 10) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_10)) { return false; }
        }
    } else if (i == 11) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_11)) { return false; }
        }
    } else {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) > SEG_11)) { return false; }
        }
    }

    return true;
}

/********            END SELF-DEFINED HEAP CHECK FUNCTIONS            ********/

/**
=======
<<<<<<< HEAD
/**
 * @brief Checks invariants specific to the "implicit list" heap representation
 *  i.e block alignment, blocks in heap boundaries, instant coalescing, etc.
 */
static bool check_heap_block(block_t *bp) {
    // checking each block's address alignment
    dbg_assert((size_t)bp % 8 == (size_t)0);

    // checking block lies withing the heap boundaries
    block_t *prologue = mem_heap_lo();
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert((word_t)prologue < (word_t)bp && (word_t)bp < (word_t)epilogue);

    // checking minimum block size requirements
    word_t header = *(word_t *)bp;
    dbg_assert(extract_size(header) >= min_block_size);

    if (!get_alloc(bp)) { // checking free heap block invariants
        // checking for matching header and footer values
        word_t footer = *header_to_footer(bp);
        dbg_assert(header == footer);

        // checking size and alloc bit flag consistencies
        dbg_assert(extract_size(header) == extract_size(footer));
        dbg_assert(extract_alloc(header) == extract_alloc(footer));
    }

    // checking coalescing: no consecutive free blocks in heap
    dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));

    // checking second lowest bit flag maintains prev_alloc status
    dbg_assert(get_alloc(bp) == get_prev_alloc(find_next(bp)));
=======
/** @brief checks 8-byte block alignment, matching headers and footers,
 *      block size requirements, and instant block coalescing
 * 
 * @param[in] prologue_block the heap prologue block
 * @param[in] bp the current block in the heap, either free or allocated
 * @param[in] epilogue_block the heap epilogue block
 * 
 * @return true if invariants maintained, false otherwise
 */
static bool check_heap_block(block_t *prologue_block, block_t *bp, block_t *epilogue_block) {
    // checking each block's address alignment
    dbg_assert((size_t)bp % 8 == (size_t)0);

    // checking block lies withing the heap boundaries
    dbg_assert((word_t)prologue_block < (word_t)bp && (word_t)bp < (word_t)epilogue_block);

    // checking for matching header and footer values
    word_t header_value = *(word_t *)bp;
    word_t footer_value = *header_to_footer(bp);
    dbg_assert(header_value == footer_value);

    // checking size and alloc bit flag consistencies
    dbg_assert(extract_size(header_value) == extract_size(footer_value));
    dbg_assert(extract_alloc(header_value) == extract_alloc(footer_value));

    // checking minimum block size requirements
    dbg_assert(extract_size(header_value) >= min_block_size);

    // checking coalescing: no consecutive free blocks in heap
    dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));

    return true;
}

/** @brief checks allocation flag, free block address validity, and linking
 * 
 * @param[in] prologue_block the heap prologue block
 * @param[in] bp the current block in the heap, either free or allocated
 * @param[in] epilogue_block the heap epilogue block
 * 
 * @return true if invariants maintained, false otherwise
 */
static bool check_free_block(block_t *prologue_block, block_t *bp, block_t *epilogue_block) {
    dbg_assert(!get_alloc(bp));

    // checking block lies withing the heap boundaries
    dbg_assert((word_t)prologue_block < (word_t)bp && (word_t)bp < (word_t)epilogue_block);

    // checking prev, next pointers are correctly linked
    if (bp->space.p[0] != NULL) {
        dbg_assert(bp->space.p[0]->space.p[1] == bp);
    }
    if (bp->space.p[1] != NULL) {
        dbg_assert(bp->space.p[1]->space.p[0] == bp);
    }

    return true;
}

<<<<<<< HEAD
/** @brief checks segregated list size matches the given class size declarations
 * 
 * @param[in] list the root of the segregated list
 * @param[in] i the index into the seg_list_array
 * 
 * @return true if invariants maintained, false otherwise
 */
static bool check_seg_list(block_t *list, int i) {
    /* defining segregation boundaries for the total 12 free list classes */
    size_t SEG_1 = 32;
    size_t SEG_2 = 48;
    size_t SEG_3 = 64;
    size_t SEG_4 = 128;
    size_t SEG_5 = 256;
    size_t SEG_6 = 512;
    size_t SEG_7 = 1024;
    size_t SEG_8 = 2048;
    size_t SEG_9 = 4096;
    size_t SEG_10 = 8192;
    size_t SEG_11 = 16384;

    if (i == 0) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_1)) { return false; }
        }
    } else if (i == 1) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_2)) { return false; }
        }
    } else if (i == 2) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_3)) { return false; }
        }
    } else if (i == 3) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_4)) { return false; }
        }
    } else if (i == 4) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_5)) { return false; }
        }
    } else if (i == 5) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_6)) { return false; }
        }
    } else if (i == 6) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_7)) { return false; }
        }
    } else if (i == 7) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_8)) { return false; }
        }
    } else if (i == 8) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_9)) { return false; }
        }
    } else if (i == 9) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_10)) { return false; }
        }
    } else if (i == 10) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_11)) { return false; }
        }
    } else {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) > SEG_11)) { return false; }
        }
    }

    return true;
}

/********            END SELF-DEFINED HEAP CHECK FUNCTIONS            ********/

/**
=======
/********            END SELF-DEFINED HEAP CHECK FUNCTIONS            ********/

/**
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @brief checks invariants for a segregated list dynamic memory allocator
 *
 * @param[in] line trace line number currently being parsed
 * @return true if all invariants are maintained, false otherwise
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
 * @brief checks specific invariants for a dynamic memory allocator
 *
 * @param[in] line
 * @return
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 */
bool mm_checkheap(int line) {

    // checking validity of prologue block
<<<<<<< HEAD
    block_t *prologue = mem_heap_lo();
    dbg_assert(get_alloc(prologue) == true);
    dbg_assert(get_size(prologue) == (size_t)0);

    // checking validity of epilogue block
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert(get_alloc(epilogue) == true);
    dbg_assert(get_size(epilogue) == (size_t)0);

    block_t *bp = heap_start;
    size_t tmp_free_count = 0;
    while (bp != epilogue) {
        dbg_assert(check_heap_block(bp));
=======
    block_t *prologue_block = mem_heap_lo();
    dbg_assert(get_alloc(prologue_block) == true);
    dbg_assert(get_size(prologue_block) == (size_t)0);

    // checking validity of epilogue block
    block_t *epilogue_block = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert(get_alloc(epilogue_block) == true);
    dbg_assert(get_size(epilogue_block) == (size_t)0);

    block_t *bp = heap_start;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
    size_t tmp_free_count = 0;
    while (bp != epilogue_block) {
        dbg_assert(check_heap_block(prologue_block, bp, epilogue_block));
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

        if (!get_alloc(bp)) { tmp_free_count++; }

        bp = find_next(bp);
    }
    dbg_assert(tmp_free_count == free_block_count);

    size_t tmp_seglist_count = 0;
    for (int i = 0; i < NUM_LISTS; i++) {
        dbg_assert(0 <= i && i <= NUM_LISTS);

        bp = seg_list_array[i];
<<<<<<< HEAD
        dbg_assert(check_seg_list(bp, i));

        while (bp != NULL) {
            dbg_assert(check_free_block(bp));

            tmp_seglist_count += 1;

            if (i == 0) { bp = bp->space.next_mini; } 
            else { bp = bp->space.p[1]; }
        }
    }
    dbg_assert(tmp_seglist_count == free_block_count);
=======
<<<<<<< HEAD
        dbg_assert(check_seg_list(bp, i));
=======
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e

        while (bp != NULL) {
            dbg_assert(check_free_block(prologue_block, bp, epilogue_block));

            tmp_seglist_count += 1;
            bp = bp->space.p[1];
        }
    }
    dbg_assert(tmp_seglist_count == free_block_count);
<<<<<<< HEAD
=======
=======
    while (bp != epilogue_block) {

        // checking each block's address alignment
        dbg_assert((size_t)bp % 8 == (size_t)0);

        // checking all blocks lie withing the heap boundaries
        dbg_assert((word_t)prologue_block < (word_t)bp && (word_t)bp < (word_t)epilogue_block);

        // checking for matching header and footer values
        word_t header_value = *(word_t *)bp;
        word_t footer_value = *header_to_footer(bp);
        dbg_assert(header_value == footer_value);

        // checking size and alloc bit flag consistencies
        dbg_assert(extract_size(header_value) == extract_size(footer_value));
        dbg_assert(extract_alloc(header_value) == extract_alloc(footer_value));

        // checking minimum block size requirements
        dbg_assert(extract_size(header_value) >= min_block_size);

        // checking coalescing: no consecutive free blocks in heap
<<<<<<< HEAD
        dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));
=======
<<<<<<< HEAD
        dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));
=======
<<<<<<< HEAD
        dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));
=======
<<<<<<< HEAD
        // dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));
=======
        dbg_assert(get_alloc(bp) || get_alloc(find_next(bp)));
>>>>>>> bc829d3 (added implicit list coalescing cases)
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524

        bp = find_next(bp);
    }

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
    // checking free list invariants
    bp = free_list_root;
    size_t tmp_count = 0;
    while (bp != NULL) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
        dbg_assert(!get_alloc(bp)); // checking block is free

        // checking prev, next pointers point properly
        if (bp->space.p[0] != NULL) {
            dbg_assert(bp->space.p[0]->space.p[1] == bp);
        }
        if (bp->space.p[1] != NULL) {
            dbg_assert(bp->space.p[1]->space.p[0] == bp);
        }
<<<<<<< HEAD
=======
=======
        dbg_assert(!get_alloc(bp));
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524

        tmp_count += 1;
        bp = bp->space.p[1];
    }
    dbg_assert(tmp_count == free_list_length);
<<<<<<< HEAD

    tmp_count = 0;
    bp = free_list_tail;
    while (bp != NULL) {
        dbg_assert(!get_alloc(bp)); // checking block is free

        // checking prev, next pointers point properly
        if (bp->space.p[0] != NULL) {
            dbg_assert(bp->space.p[0]->space.p[1] == bp);
        }
        if (bp->space.p[1] != NULL) {
            dbg_assert(bp->space.p[1]->space.p[0] == bp);
        }

        tmp_count += 1;
        bp = bp->space.p[0];
    }
    dbg_assert(tmp_count == free_list_length);
=======
<<<<<<< HEAD
=======
=======
    // check each block’s header and footer: previous/next
>>>>>>> 4e7b9003c3ccd586061100bbe801917abf2d97f9
>>>>>>> 8b1ad44c2f8071e07fca46bd691bbfdf40ebd919
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    return true;
}

/**
<<<<<<< HEAD
 * @brief initializes the heap, resetting all internal structs
 *
=======
<<<<<<< HEAD
 * @brief Checking free block invariants specific to the segregated free lists
 *  i.e bit flags, blocks in heap bounds, linking pointers are correct
 */
static bool check_free_block(block_t *bp) {
    // ensuring bit flags indicate free block
    dbg_assert(!get_alloc(bp) && !get_prev_alloc(find_next(bp)));

    // checking block lies withing the heap boundaries
    block_t *prologue = mem_heap_lo();
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert((word_t)prologue < (word_t)bp && (word_t)bp < (word_t)epilogue);

    // checking prev, next pointers are correctly linked
    if (bp->space.p[0] != NULL) {
        dbg_assert(bp->space.p[0]->space.p[1] == bp);
    }
    if (bp->space.p[1] != NULL) {
        dbg_assert(bp->space.p[1]->space.p[0] == bp);
    }

    return true;
}

/** @brief Checking segregated free list block size match class demarcations */
static bool check_seg_list(block_t *list, int i) {
    /* defining segregation boundaries for the total 12 free list classes */
    size_t SEG_1 = 32;
    size_t SEG_2 = 48;
    size_t SEG_3 = 64;
    size_t SEG_4 = 128;
    size_t SEG_5 = 256;
    size_t SEG_6 = 512;
    size_t SEG_7 = 1024;
    size_t SEG_8 = 2048;
    size_t SEG_9 = 4096;
    size_t SEG_10 = 8192;
    size_t SEG_11 = 16384;

    if (i == 0) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_1)) { return false; }
        }
    } else if (i == 1) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_2)) { return false; }
        }
    } else if (i == 2) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_3)) { return false; }
        }
    } else if (i == 3) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_4)) { return false; }
        }
    } else if (i == 4) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_5)) { return false; }
        }
    } else if (i == 5) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_6)) { return false; }
        }
    } else if (i == 6) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_7)) { return false; }
        }
    } else if (i == 7) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_8)) { return false; }
        }
    } else if (i == 8) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_9)) { return false; }
        }
    } else if (i == 9) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_10)) { return false; }
        }
    } else if (i == 10) {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) <= SEG_11)) { return false; }
        }
    } else {
        for (block_t *p = list; p != NULL; p = p->space.p[1]) {
            if (!(get_size(p) > SEG_11)) { return false; }
        }
    }

    return true;
}

static void print_block(block_t *bp) {
    size_t size = get_size(bp);
    bool prev_alloc = get_prev_alloc(bp);
    bool alloc = get_alloc(bp);

    printf("      size: %lu, prev_alloc: %d, alloc: %d\n", size, prev_alloc, alloc);
}

static void print_heap() {
    block_t *bp = heap_start;
    block_t *epilogue_block = (block_t *)((char *)mem_heap_hi() - 7);

    while (bp != epilogue_block) {
        print_block(bp);
        bp = find_next(bp);
    }
}

/********            END SELF-DEFINED HEAP CHECK FUNCTIONS            ********/

/**
 * @brief checks invariants for a segregated list dynamic memory allocator
 *
 * @param[in] line trace line number currently being parsed
 * @return true if all invariants are maintained, false otherwise
 */
bool mm_checkheap(int line) {

    // checking validity of prologue block
    block_t *prologue = mem_heap_lo();
    dbg_assert(get_alloc(prologue) == true);
    dbg_assert(get_size(prologue) == (size_t)0);

    // checking validity of epilogue block
    block_t *epilogue = (block_t *)((char *)mem_heap_hi() - 7);
    dbg_assert(get_alloc(epilogue) == true);
    dbg_assert(get_size(epilogue) == (size_t)0);

    block_t *bp = heap_start;
    size_t tmp_free_count = 0;
    while (bp != epilogue) {
        dbg_assert(check_heap_block(bp));

        if (!get_alloc(bp)) { tmp_free_count++; }

        bp = find_next(bp);
    }
    dbg_assert(tmp_free_count == free_block_count);

    size_t tmp_seglist_count = 0;
    for (int i = 0; i < NUM_LISTS; i++) {
        dbg_assert(0 <= i && i <= NUM_LISTS);

        bp = seg_list_array[i];
        dbg_assert(check_seg_list(bp, i));

        while (bp != NULL) {
            dbg_assert(check_free_block(bp));

            tmp_seglist_count += 1;
            bp = bp->space.p[1];
        }
    }
    dbg_assert(tmp_seglist_count == free_block_count);

    return true;
}

/**
 * @brief initializes the heap, resetting all internal structs
 *
=======
 * @brief initializes the heap, resetting all internal structs
 *
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 * @return true if initialization worked, false otherwise
 */
bool mm_init(void) {
    // Create the initial empty heap
    word_t *start = (word_t *)(mem_sbrk(2 * wsize));

    if (start == (void *)-1) {
        return false;
    }

<<<<<<< HEAD
    /* heap prologue and epilogue help with heap structure invariants, as they 
        mark allocated space where the heap cannot go beyond unless extended */

    // default specifications
    start[0] = pack(0, false, true, true); // Heap prologue (block footer)
    start[1] = pack(0, false, true, true); // Heap epilogue (block header)
=======
<<<<<<< HEAD
    /* heap prologue and epilogue help with heap structure invariants, as they 
=======
    /* heap prologue and epilogue help with heap structure invariants,as they 
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
        mark allocated space where the heap cannot go beyond unless extended */

    // default specifications
    start[0] = pack(0, true, true); // Heap prologue (block footer)
    start[1] = pack(0, true, true); // Heap epilogue (block header)
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // initializing data structures
    heap_start = NULL;
    free_block_count = 0;
    for (int i = 0; i < NUM_LISTS; i++) { seg_list_array[i] = NULL; }
<<<<<<< HEAD
=======

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
    // initializing data structures
    heap_start = NULL;
    free_block_count = 0;
    for (int i = 0; i < NUM_LISTS; i++) { seg_list_array[i] = NULL; }
<<<<<<< HEAD
=======
=======
    // Initializing data structure pointers
    heap_start = NULL;
    free_list_root = NULL;
<<<<<<< HEAD
    free_list_tail = NULL;
=======
>>>>>>> 79a94b1bb71c731c1926358ca60019e6a47a9524
    free_list_length = 0;
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // Heap starts with first "block header", currently the epilogue
    heap_start = (block_t *)&(start[1]);

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        return false;
    }

    return true;
}

/**
 * @brief allocates a requested space on the heap
 * 
 * @pre size is non-negative
 *
 * @param[in] size the requested allocation space
<<<<<<< HEAD
 * @return a pointer to the start of the payload space, NULL otherwise
=======
<<<<<<< HEAD
 * @return a pointer to the start of the payload space, NULL otherwise
=======
<<<<<<< HEAD
 * @return a pointer to the start of the payload space, NULL otherwise
=======
<<<<<<< HEAD
 * @return a pointer to the start of the payload space, NULL otherwise
=======
 * @return a pointer to the start of the allocated space, NULL otherwise
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90
 */
void *malloc(size_t size) {
    dbg_requires(mm_checkheap(__LINE__));

    size_t asize;      // Adjusted block size
    size_t extendsize; // Amount to extend heap if no fit is found
    block_t *block;
    void *bp = NULL;

    // Initialize heap if it isn't initialized
    if (heap_start == NULL) {
        if (!(mm_init())) {
            dbg_printf("Problem initializing heap. Likely due to sbrk");
            return NULL;
        }
    }

    // Ignore spurious request
    if (size == 0) {
        dbg_ensures(mm_checkheap(__LINE__));
        return bp;
    }

    // Adjust block size to include overhead and to meet alignment requirements
    asize = round_up(size + wsize, dsize);

    // Search the free list for a fit
    block = find_fit(asize);

    // If no fit is found, request more memory, and then and place the block
    if (block == NULL) {
        // Always request at least chunksize
        extendsize = max(asize, chunksize);
        block = extend_heap(extendsize);
        // extend_heap returns an error
        if (block == NULL) {
            return bp;
        }
    }

    // The block should be marked as free
    dbg_assert(!get_alloc(block));

<<<<<<< HEAD
    remove_from_seg_list(block);

    // Mark block as allocated
    size_t block_size = get_size(block);
    write_block(block, block_size, get_prev_mini(block), get_prev_alloc(block), true);
=======
<<<<<<< HEAD
    remove_from_seg_list(block);
=======
<<<<<<< HEAD
    remove_from_seg_list(block);
=======
<<<<<<< HEAD
    remove_from_seg_list(block);
=======
    remove_from_free_list(block);
>>>>>>> da0d3cb7664cc3c02f688277636f3fb80de2565c
>>>>>>> e35841e34e7548fdc10754319d9b8ac36aa14b4e
>>>>>>> 244cc523a220e27fe73fa602ec836ac31b6e9dfd

    // Mark block as allocated
    size_t block_size = get_size(block);
    write_block(block, block_size, get_prev_alloc(block), true);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // Try to split the block if too large
    split_block(block, asize);

    bp = header_to_payload(block);

    dbg_ensures(mm_checkheap(__LINE__));

    return bp;
}

/**
 * @brief "removes" the block (pointed by bp) from the heap
 * 
 * @pre The block must be a valid, malloc'd block, not a boundary tag.
 *
 * @param[in] bp pointer to the block's payload
 */
void free(void *bp) {
    dbg_requires(mm_checkheap(__LINE__));

    if (bp == NULL) {
        return;
    }

    block_t *block = payload_to_header(bp);
    size_t size = get_size(block);

    // The block should be marked as allocated
    dbg_assert(get_alloc(block));

    // Mark the block as free
<<<<<<< HEAD
    write_block(block, size, get_prev_mini(block), get_prev_alloc(block), false);
=======
    write_block(block, size, get_prev_alloc(block), false);
>>>>>>> adef05a545547a4b6a52018abe8807e09f104a90

    // Try to coalesce the block with its neighbors
    coalesce_block(block);

    dbg_ensures(mm_checkheap(__LINE__));
}

/**
 * @brief allocates a newly sized block and copies over old contents (up to size)
 * 
 * @pre ptr maps to a valid block in the heap
 * @pre size is non-negative
 *
 * @param[in] ptr pointer to the contents (payload) of the malloc'd block
 * @param[in] size requested size of the reallocation
 * @return a pointer to the reallocated payload space (with copied contents)
 */
void *realloc(void *ptr, size_t size) {
    block_t *block = payload_to_header(ptr);
    size_t copysize;
    void *newptr;

    // If size == 0, then free block and return NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // If ptr is NULL, then equivalent to malloc
    if (ptr == NULL) {
        return malloc(size);
    }

    // Otherwise, proceed with reallocation
    newptr = malloc(size);

    // If malloc fails, the original block is left untouched
    if (newptr == NULL) {
        return NULL;
    }

    // Copy the old data
    copysize = get_payload_size(block); // gets size of old payload
    if (size < copysize) {
        copysize = size;
    }
    memcpy(newptr, ptr, copysize);

    // Free the old block
    free(ptr);

    return newptr;
}

/**
 * @brief allocates elements * size space, initializing each value to 0
 * 
 * @pre elements and size are both non-negative
 *
 * @param[in] elements the number of elements to allocate (in bytes)
 * @param[in] size the size of each element (in bytes)
 * @return a pointer to the allocated block's payload
 */
void *calloc(size_t elements, size_t size) {
    void *bp;
    size_t asize = elements * size;

    if (elements == 0) {
        return NULL;
    }
    if (asize / elements != size) {
        // Multiplication overflowed
        return NULL;
    }

    bp = malloc(asize);
    if (bp == NULL) {
        return NULL;
    }

    // Initialize all bits to 0
    memset(bp, 0, asize);

    return bp;
}

/*
 *****************************************************************************
 * Do not delete the following super-secret(tm) lines!                       *
 *                                                                           *
 * 53 6f 20 79 6f 75 27 72 65 20 74 72 79 69 6e 67 20 74 6f 20               *
 *                                                                           *
 * 66 69 67 75 72 65 20 6f 75 74 20 77 68 61 74 20 74 68 65 20               *
 * 68 65 78 61 64 65 63 69 6d 61 6c 20 64 69 67 69 74 73 20 64               *
 * 6f 2e 2e 2e 20 68 61 68 61 68 61 21 20 41 53 43 49 49 20 69               *
 *                                                                           *
 * 73 6e 27 74 20 74 68 65 20 72 69 67 68 74 20 65 6e 63 6f 64               *
 * 69 6e 67 21 20 4e 69 63 65 20 74 72 79 2c 20 74 68 6f 75 67               *
 * 68 21 20 2d 44 72 2e 20 45 76 69 6c 0a c5 7c fc 80 6e 57 0a               *
 *                                                                           *
 *****************************************************************************
 */
