/*
 * This file is generated from 363 of the 738 RARE rewrite rules (define-rule)
 * in gpt-6-luna.
 * Do not edit by hand.
 *
 * For each rule, a match function matches the rule's pattern against a node
 * in Bitwuzla's normal form, and a build function constructs the rewritten
 * node via Rewriter::mk_node().
 *
 * - Ground subterms of a pattern, e.g., (bvnot (@bv 0 (@bvsize x0))), are
 *   evaluated and only match the corresponding value (Bitwuzla always
 *   evaluates operators applied to values).
 * - The children of commutative operators (bvadd, bvmul, bvand, bvxor, and,
 *   =) are matched in any order.
 * - Rules that are not valid for bit-width 1 only apply to terms of
 *   bit-width >= 2 (checked by exhaustive evaluation at generation time).
 * - Rules whose result is rewritten by the built-in rewrite rules at
 *   bit-width 1 only apply to terms of bit-width >= 2. At bit-width 1, the
 *   built-in rewrite rules also rewrite the match patterns of these rules
 *   (e.g., bvadd to bvxor), i.e., the rules are not applicable at bit-width
 *   1 anyway.
 * - Rules are tried in order of priority: rules with larger patterns first,
 *   then rules with fewer variables.
 *
 * Only rules whose result is in normal form w.r.t. the built-in rewrite
 * rules (up to the order of the children of commutative operators) are
 * included, since otherwise rewriting the result of a rule may lead back to
 * its match pattern, i.e., the rule has no effect or introduces a rewrite
 * cycle.
 *
 * 375 rules of the rule set are excluded since the built-in rewrite rules
 * rewrite their result
 * - back to their match pattern, i.e., they have no effect (46):
 *   add-all-ones-as-negation, add-negated-xor-and, all-ones-add-to-negated-sum,
 *   and-negated-self-zero-test, and-nonzero-lowbit-mask, ashr-complement-add,
 *   bvadd-all-ones-rewrite, bvadd-all-ones-to-not-neg,
 *   bvadd-complement-simplify, bvadd-minus-one-and-xor,
 *   bvadd-negated-rounded-shift, bvadd-not-complement-simplify,
 *   bvadd-not-subsumed, bvadd-not-zero-not, bvadd-not-zero-x-as-negation,
 *   bvand-add-minus-one-simplify, bvand-no-carry-self, bvand-self-minus-one,
 *   bvnot-add-as-negated-increment, bvnot-add-minus-one-3,
 *   bvnot-add-negated-complement, bvnot-add-negation-simplification,
 *   bvnot-minus-one-and, bvnot-minus-one-xor, bvnot-negated-increment,
 *   bvnot-plus-negated-zero, bvnot-zero-plus-complement,
 *   bvnot-zero-plus-negated-x, bvnot-zero-plus-x, bvnot-zero-plus-x-as-neg,
 *   bvnot-zero-plus-x-to-not-neg-x, collapse-complemented-add,
 *   combine-complemented-addends, combine-complements-and-addends,
 *   complemented-xor-plus-one, fold-negated-one-and-not,
 *   fold-negated-zero-offset, not-add-xor-mask, not-minus-one-plus-one,
 *   not-x-and-not-increment, simplify-all-ones-add-and,
 *   simplify-complemented-offset, simplify-negated-add-shift, sum-minus-one,
 *   xor-add-complement-simplify, xor-negated-sum.
 * - to a different term (329): add-complement-negated-increment,
 *   add-minus-shift-negation, add-negated-one, add-not-zero-as-negation,
 *   add-with-carry-from-masked-bit, add-zero-negated-equality,
 *   add-zero-negation-equality, add-zero-test-as-negation,
 *   all-ones-plus-product, all-ones-plus-x-unsigned-compare,
 *   all-ones-xor-self-and-neg, and-not-add-shifted-ones, and-self-minus-one,
 *   ashr-add-negated-complement, ashr-add-one-zero-test,
 *   ashr-complement-negate, ashr-negated-input, ashr-rounded-double-plus-one,
 *   ashr-shifted-double, ashr-simplified-complement-add, ashr-sub-one-add,
 *   bv-add-all-ones-as-negation, bv-add-all-ones-ult, bv-add-all-ones-ult-2,
 *   bv-add-complement-to-sub, bv-negated-addend-unsigned-bound, bv-negated-sum,
 *   bv-not-add-one-simplify, bv-not-zero-plus-x-compare, bv-one-hot-mask-test,
 *   bv-sub-decremented-right, bv-xor-self-and-negation-minus-one,
 *   bv-zero-test-lowest-set-bit, bvadd-all-ones-and-one, bvadd-all-ones-ult,
 *   bvadd-all-ones-ult-2, bvadd-all-ones-ult-negation,
 *   bvadd-allones-to-negated-sum-minus-one, bvadd-allones-x0,
 *   bvadd-allones-x0-negation, bvadd-bvnot-zero-sum,
 *   bvadd-carry-constant-complement, bvadd-complement-and-cancel,
 *   bvadd-complement-minus-one, bvadd-complement-or, bvadd-complement-subtract,
 *   bvadd-double-decrement-distribute, bvadd-fold-complement,
 *   bvadd-fold-complement-zero, bvadd-minus-one-as-complement-negation,
 *   bvadd-minus-one-ult, bvadd-minus-one-unsigned-comparison,
 *   bvadd-minus-one-via-negation, bvadd-neg-one-and-decrement,
 *   bvadd-negated-complement-to-sub, bvadd-negated-sum,
 *   bvadd-negated-x-rewrite, bvadd-negated-zero-and-duplicate-add,
 *   bvadd-negated-zero-and-sum, bvadd-negated-zero-plus-x-to-sub,
 *   bvadd-negation-cancellation, bvadd-negative-one-mask,
 *   bvadd-nonzero-via-negation, bvadd-not-complement-collapse,
 *   bvadd-not-complement-simplify-2, bvadd-not-less-than-left,
 *   bvadd-not-negated-adjustment, bvadd-not-one-xor-and, bvadd-not-plus-one,
 *   bvadd-not-sub-complement, bvadd-not-zero-as-negation, bvadd-not-zero-bvsub,
 *   bvadd-not-zero-to-negation-complement, bvadd-not-zero-to-subtraction,
 *   bvadd-plus-one-carry, bvadd-zero-equality-neg,
 *   bvadd-zero-five-term-isolation, bvadd-zero-sum-negation,
 *   bvand-demorgan-simplify, bvand-increment-minus-one-factor,
 *   bvand-minus-one-normalization, bvand-not-add-shift-mask,
 *   bvashr-add-sub-reassociation, bvashr-complement-neg, bvnot-add-minus-one,
 *   bvnot-add-minus-one-2, bvnot-add-minus-one-to-neg, bvnot-add-neg,
 *   bvnot-add-neg-2, bvnot-add-neg-one, bvnot-add-neg-one-sum,
 *   bvnot-add-neg-sum, bvnot-add-negate, bvnot-add-negate-identity,
 *   bvnot-add-negated-complement-sum, bvnot-add-negated-ones,
 *   bvnot-add-negation, bvnot-add-negation-offset, bvnot-add-negation-simplify,
 *   bvnot-add-one-cancel, bvnot-add-one-complement, bvnot-add-one-complement-2,
 *   bvnot-add-ones-to-neg-sum, bvnot-add-to-bvneg, bvnot-add-to-neg,
 *   bvnot-add-to-one-minus-sum, bvnot-add-with-minus-one, bvnot-add-xor-carry,
 *   bvnot-add-zero-minus-one, bvnot-add-zero-minus-one-2,
 *   bvnot-all-ones-addend, bvnot-all-ones-plus-x-to-neg,
 *   bvnot-allones-add-to-negated-sum, bvnot-allones-plus-x0,
 *   bvnot-and-add-all-ones-shift, bvnot-ashr-negate-sum,
 *   bvnot-neg-as-decrement, bvnot-nested-add-to-sub, bvnot-of-add-xor,
 *   bvnot-plus-one-cancel, bvnot-sum-of-incremented-operands,
 *   bvnot-sum-plus-one, bvnot-sum-plus-one-2, bvnot-sum-split,
 *   bvnot-sum-to-neg, bvnot-sum-with-all-ones, bvnot-xor-add-mask,
 *   bvnot-xor-add-neg-xor, bvnot-xor-negated-addend, bvnot-zero-add-one,
 *   bvnot-zero-add-unsigned-compare, bvnot-zero-add-unsigned-less,
 *   bvnot-zero-as-negative-one, bvnot-zero-plus-unsigned-boundary,
 *   bvnot-zero-plus-x-as-complement-neg, bvslt-add-complement-sign-overflow,
 *   bvslt-add-one-overflow, bvslt-add-one-signed-boundary,
 *   bvslt-negated-sum-plus-x, bvslt-self-plus-sum, bvslt-sum-plus-one,
 *   bvslt-sum-plus-one-2, bvslt-sum-plus-one-3, bvslt-sum-plus-one-4,
 *   bvslt-zero-add-not-sum, bvuge-sum-plus-one, bvult-add-one-rewrite,
 *   bvult-add-sum, bvult-negated-all-ones-add, bvult-shared-addend,
 *   bvult-shared-addend-2, bvult-shared-addend-3, bvult-sum-plus-one,
 *   bvxor-masked-complement, cancel-common-addend-unsigned-order,
 *   cancel-complementary-addends-signed, collapse-all-ones-addends,
 *   collapse-all-ones-addition-2, collapse-complement-addends,
 *   collapse-complemented-addends-5, collapse-complemented-addends-6,
 *   collapse-minus-one-addends, collapse-minus-one-addends-3,
 *   collapse-nested-add-before-complement, combine-complemented-addend,
 *   combine-complemented-addend-2, combine-complemented-addend-3,
 *   combine-complemented-addends-4, combine-masked-bit-and-addition,
 *   combine-minus-one-addends, combine-minus-ones, combine-negated-addends,
 *   combine-offset-addends, complement-add-mask, complement-sum-plus-one,
 *   complemented-sum-to-negation, decremented-max-add-compare,
 *   demorgan-factor-common-and, double-negated-subtraction,
 *   double-x-via-add-inverse, factor-common-bitvector-multiplier,
 *   factor-common-multiplier-2, factor-common-product,
 *   factor-multiply-equality, fold-all-ones-addends, fold-all-ones-additions,
 *   fold-complemented-addend, fold-complemented-sum, fold-minus-one-into-shift,
 *   fold-negative-one-into-shift, fold-sign-extension-arithmetic,
 *   mask-x-by-nonzero, masked-decrement-xor, masked-xor-intersection,
 *   merge-complemented-addend, move-addend-and-complement,
 *   negated-add-zero-guard, negated-and-add-shift, negated-arithmetic-shift,
 *   negated-arithmetic-shift-simplify, negated-sum-of-complements,
 *   negated-sum-plus-one, negated-sum-to-subtraction, nested-add-subtraction,
 *   nested-complemented-add-to-sub, nested-twos-complement-subtraction,
 *   nonzero-and-negation, nonzero-lowbit-intersection, nonzero-lowest-set-bit,
 *   nonzero-sum-as-negated-operands-distinct, normalize-complemented-addends,
 *   normalize-double-complement-sub, normalize-negated-ones-addition,
 *   not-add-negate-simplify, not-add-zero-complement,
 *   not-all-ones-plus-sum-to-neg, not-allones-plus-to-neg,
 *   not-and-add-shift-simplify, not-arithmetic-shift-add,
 *   not-arithmetic-shift-add-neg, not-arithmetic-shift-minus-one,
 *   not-of-sum-minus-one, not-sum-to-negated-sum, not-unit-add-equality,
 *   positive-nonzero-sum, reassociate-complemented-addends,
 *   rewrite-shifted-mask-add, shared-addition-unsigned-compare,
 *   signed-add-boundary, signed-add-compare-increment,
 *   signed-add-constant-one-compare, signed-add-minus-one-lt,
 *   signed-add-one-compare, signed-add-one-comparison,
 *   signed-add-one-comparison-2, signed-add-order-overflow,
 *   signed-cancel-add-not, signed-compare-add-one, signed-compare-add-one-2,
 *   signed-compare-sum-plus-one, signed-decrement-compare,
 *   signed-decrement-less-than, signed-decrement-less-than-2,
 *   signed-decrement-less-than-3, signed-decrement-less-than-4,
 *   signed-decrement-less-than-5, signed-decrement-less-than-6,
 *   signed-ge-add-one, signed-ge-add-one-boundary, signed-ge-incremented-sum,
 *   signed-increment-compare, signed-increment-comparison,
 *   signed-increment-less-than, signed-increment-not-positive,
 *   signed-less-add-one, signed-less-add-one-to-rhs, signed-less-add-rewrite,
 *   signed-less-than-add-one, signed-less-than-add-one-2,
 *   signed-less-than-add-one-3, signed-less-than-add-one-4,
 *   signed-less-than-add-one-5, signed-less-than-add-one-6,
 *   signed-less-than-add-one-7, signed-less-than-add-wrap,
 *   signed-less-than-increment, signed-less-than-increment-2,
 *   signed-less-than-incremented-sum, signed-less-than-self-plus-sum,
 *   signed-less-than-sum-overflow, signed-less-than-sum-plus-one,
 *   signed-less-than-sum-plus-one-2, signed-less-than-sum-plus-one-3,
 *   signed-less-than-sum-plus-one-4, signed-less-than-zero-subtraction,
 *   signed-lt-add-one, signed-min-plus-one-compare,
 *   signed-negated-sum-condition, signed-positive-add-one,
 *   signed-positive-difference-test, signed-positive-increment-sum,
 *   signed-positive-sum-plus-one, signed-positive-sum-plus-one-2,
 *   signed-predecessor-compare, signed-sum-increment-compare,
 *   signed-sum-increment-nonnegative, signed-sum-nonpositive,
 *   signed-sum-not-positive, signed-sum-plus-one-nonpositive,
 *   signed-sum-plus-one-nonpositive-2, signed-sum-plus-one-positive,
 *   signed-sum-plus-one-positive-2, signed-sum-plus-one-positive-3,
 *   signed-sum-positive-after-increment, signed-sum-positive-by-sign-and-max,
 *   simplify-add-arithmetic-shift, simplify-arithmetic-shift,
 *   simplify-arithmetic-shift-correction, simplify-arithmetic-shift-negation,
 *   simplify-cancel-complemented-sum-signed-less-than,
 *   simplify-complement-add-one, simplify-complemented-add-subtraction,
 *   simplify-complemented-addition, simplify-complemented-sum-2,
 *   simplify-minus-one-arithmetic-shift, simplify-negated-arithmetic-shift-3,
 *   simplify-nested-bitvector-negation, simplify-shifted-all-ones-subtract,
 *   simplify-sign-adjusted-sum, subtract-via-complemented-add,
 *   sum-minus-one-as-not-neg, sum-plus-one-unsigned-compare,
 *   unsigned-add-overflow-comparison, xor-add-minus-one, xor-add-negated-sum,
 *   xor-add-one-complement, xor-and-difference-expansion,
 *   xor-and-negation-rewrite, xor-difference-common-base,
 *   xor-incremented-sum-complement, xor-negated-lowbit,
 *   xor-negation-add-all-ones, xor-product-difference, xor-with-negated-sum,
 *   xor-x-and-neg-x, zero-sum-pair-rebalance, zero-sum-to-negated-addition,
 *   zero-test-lowest-set-bit, zero-test-lsb-mask.
 */

#include "rewrite/rewrites_rare.h"

#include <cassert>
#include <vector>

#include "bv/bitvector.h"
#include "node/node_kind.h"
#include "node/node_manager.h"
#include "rewrite/rewriter.h"

namespace bzla {

using namespace node;

namespace {

/* --- Helpers -------------------------------------------------------------- */

/** @return True if node is a bit-vector value. */
bool
is_bv_value(const Node& node)
{
  return node.is_value() && node.type().is_bv();
}

/** @return True if node is the bit-vector value zero. */
bool
is_zero(const Node& node)
{
  return is_bv_value(node) && node.value<BitVector>().is_zero();
}

/** @return True if node is the bit-vector value one. */
bool
is_one(const Node& node)
{
  return is_bv_value(node) && node.value<BitVector>().is_one();
}

/** @return True if node is the bit-vector value ones. */
bool
is_ones(const Node& node)
{
  return is_bv_value(node) && node.value<BitVector>().is_ones();
}

/* --- Rules ---------------------------------------------------------------- */

// (define-rule additive-cancel-ones ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//       x1)
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_additive_cancel_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x0 = n8[0];
        const Node& x1 = n2[1 - i4];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n3[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_additive_cancel_ones(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule add-all-ones-cancel ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x0
//         (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvadd (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_add_all_ones_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ASHR || !is_one(n10))
          {
            continue;
          }
          if (!is_one(n9[1]))
          {
            continue;
          }
          const Node& x1 = n9[0];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_add_all_ones_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule add-complemented-negation ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0))))
//   x1)
bool
match_add_complemented_negation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (n6.kind() != Kind::BV_NOT || !is_one(n7))
        {
          continue;
        }
        if (n6[0] != x0)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_add_complemented_negation(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[1];
}

// (define-rule add-complement-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvadd x0 (bvnot x1)) (bvadd x1 (@bv 1 (@bvsize x0))))
//   x0)
bool
match_add_complement_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      const Node& x1 = n5[0];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n8))
        {
          continue;
        }
        if (n7 != x1)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_add_complement_cancel(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[0];
}

// (define-rule add-negated-zero-offset ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_add_negated_zero_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n3[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_add_negated_zero_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule add-not-sum-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd x0 (bvnot (bvadd x0 x1)))
//   (bvnot x1))
bool
match_add_not_sum_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& x0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5 != x0)
      {
        continue;
      }
      const Node& x1 = n3[1 - i4];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_add_not_sum_cancel(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  return t1;
}

// (define-rule add-not-sum-with-offset ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0)))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd (bvadd (bvnot x0) (bvnot x1)) (bvadd x2 (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_add_not_sum_with_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& n7 = n5[0];
      if (n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n3[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_add_not_sum_with_offset(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t4});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t3, t5});
  return t6;
}

// (define-rule add-one-via-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvadd (bvadd (bvadd x0 x1) (bvadd x2 x3)) (@bv 1 (@bvsize x0))) x4)
//   (bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x2 x3 x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_add_one_via_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x0 = n7[i9];
          const Node& x1 = n7[1 - i9];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& x2 = n8[i10];
            const Node& x3 = n8[1 - i10];
            const Node& x4 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_add_one_via_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, vars[2]});
  Node t6 = rewriter.mk_node(Kind::BV_ADD, {t5, vars[3]});
  Node t7 = rewriter.mk_node(Kind::BV_ADD, {t6, vars[4]});
  return t7;
}

// (define-rule add-one-via-complemented-sum-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvxor x0 (bvxor x1 x2)) (bvadd x3 (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd (bvnot x3) (bvnot (bvxor x0 (bvxor x1 x2))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_add_one_via_complemented_sum_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_XOR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n5[i6];
        const Node& x2 = n5[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[1 - i7];
          if (!is_one(n8))
          {
            continue;
          }
          const Node& x3 = n3[i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_add_one_via_complemented_sum_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_XOR, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t1, t4});
  Node t6 = rewriter.mk_node(Kind::BV_NOT, {t5});
  return t6;
}

// (define-rule ashr-add-one-nontrivial ((x0 ?BitVec))
//   (not
//     (=
//       (@bv 0 (@bvsize x0))
//       (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//   (and
//     (not (= x0 (@bv 0 (@bvsize x0))))
//     (not (= x0 (bvnot (@bv 0 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the rule is not valid
// for bit-width 1, e.g., for x0 = 0.
bool
match_ashr_add_one_nontrivial(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_zero(n3) || n4.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& n5 = n4[0];
    if (n5.kind() != Kind::BV_ADD || !is_one(n4[1]))
    {
      continue;
    }
    for (size_t i6 = 0; i6 < 2; ++i6)
    {
      const Node& n7 = n5[1 - i6];
      if (!is_one(n7))
      {
        continue;
      }
      const Node& x0 = n5[i6];
      // Not valid for bit-width 1.
      if (x0.type().bv_size() < 2)
      {
        continue;
      }
      vars[0] = x0;
      return true;
    }
  }
  return false;
}

Node
build_ashr_add_one_nontrivial(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_zero(size));
  Node t2         = rewriter.mk_node(Kind::EQUAL, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::NOT, {t2});
  Node t4         = nm.mk_value(BitVector::mk_ones(size));
  Node t5         = rewriter.mk_node(Kind::EQUAL, {vars[0], t4});
  Node t6         = rewriter.mk_node(Kind::NOT, {t5});
  Node t7         = rewriter.mk_node(Kind::AND, {t3, t6});
  return t7;
}

// (define-rule ashr-complement-add-rounding ((x0 ?BitVec))
//   (bvnot
//     (bvashr
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (@bv 1 (@bvsize x0))))
//   (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_complement_add_rounding(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD || !is_one(n1[1]))
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[i3];
    const Node& n5 = n2[1 - i3];
    if (!is_ones(n4) || n5.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& x0 = n5[0];
    vars[0]        = x0;
    return true;
  }
  return false;
}

Node
build_ashr_complement_add_rounding(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  return t3;
}

// (define-rule ashr-complement-negated-input ((x0 ?BitVec))
//   (bvashr
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_complement_negated_input(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_ones(n3) || n4.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& x0 = n4[0];
    vars[0]        = x0;
    return true;
  }
  return false;
}

Node
build_ashr_complement_negated_input(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule ashr-half-sum-fold ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//     (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_half_sum_fold(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[i7];
        const Node& n9 = n3[1 - i7];
        if (n8.kind() != Kind::BV_ASHR || !is_one(n9))
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x1 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_ashr_half_sum_fold(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule ashr-negated-increment ((x0 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvashr (bvnot x0) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvand x0 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_negated_increment(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_NOT || !is_one(n5[1]))
      {
        continue;
      }
      if (n6[0] != x0)
      {
        continue;
      }
      vars[0] = x0;
      return true;
    }
  }
  return false;
}

Node
build_ashr_negated_increment(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_AND, {vars[0], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule ashr-negated-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_negated_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_NOT || !is_one(node[1]))
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[1 - i3];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[i3];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x1 = n4[i5];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_ashr_negated_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = nm.mk_value(BitVector::mk_one(size));
  Node t5         = rewriter.mk_node(Kind::BV_ASHR, {t3, t4});
  return t5;
}

// (define-rule ashr-negated-sum-split ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2)
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x2 (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_negated_sum_split(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n4 = n3[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_ashr_negated_sum_split(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t2});
  Node t5         = nm.mk_value(BitVector::mk_one(size));
  Node t6         = rewriter.mk_node(Kind::BV_ASHR, {t4, t5});
  return t6;
}

// (define-rule ashr-plus-low-bit ((x0 ?BitVec))
//   (bvadd x0
//     (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvand x0 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_plus_low_bit(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      if (n6[0] != x0)
      {
        continue;
      }
      vars[0] = x0;
      return true;
    }
  }
  return false;
}

Node
build_ashr_plus_low_bit(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_AND, {vars[0], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule ashr-simplify-add-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_simplify_add_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_ashr_simplify_add_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule ashr-subtract-one-complement ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_subtract_one_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (n8.kind() != Kind::BV_NOT || !is_one(n9))
        {
          continue;
        }
        const Node& x1 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_ashr_subtract_one_complement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule ashr-sum-after-cancelled-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)
//       (@bv 1 (@bvsize x0)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_sum_after_cancelled_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || !is_one(n4))
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          const Node& x2 = n3[1 - i5];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_ashr_sum_after_cancelled_offset(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule ashr-sum-cancel-ones ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd x0
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvadd x2 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_sum_cancel_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x1 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_ashr_sum_cancel_ones(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule ashr-sum-minus-one-half ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//       (@bv 1 (@bvsize x0)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_sum_minus_one_half(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || !is_one(n4))
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n6[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_ashr_sum_minus_one_half(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule ashr-sum-offset-cancel ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd x0
//       (bvadd
//         (@bv 1 (@bvsize x0))
//         (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_ashr_sum_offset_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n6[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_ashr_sum_offset_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule average-floor-signed-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0)))
//     (bvadd x0 x1))
//   (bvadd
//     (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))
//     (bvand (bvadd x0 x1) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_average_floor_signed_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& n7 = n5[0];
      if (n7.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& n8 = n7[0];
      if (n8.kind() != Kind::BV_ADD || !is_one(n7[1]))
      {
        continue;
      }
      for (size_t i9 = 0; i9 < 2; ++i9)
      {
        const Node& x0 = n8[i9];
        const Node& x1 = n8[1 - i9];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n3[i10];
          const Node& n12 = n3[1 - i10];
          if (n11 != x0)
          {
            continue;
          }
          if (n12 != x1)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_average_floor_signed_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_AND, {t1, t2});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t3, t4});
  return t5;
}

// (define-rule bvadd-allones-equality-reverse
//     ((x0 ?BitVec) (p0 Bool) (x1 ?BitVec) (x2 ?BitVec))
//   (and
//     (and (= (@bv 0 (@bvsize x0)) x0) p0)
//     (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//   (and p0
//     (and
//       (= x0 (@bv 0 (@bvsize x0)))
//       (= (bvadd x2 (@bv 1 (@bvsize x0))) x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_allones_equality_reverse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (!is_zero(n7))
        {
          continue;
        }
        if (!n5[1 - i6].type().is_bv())
        {
          continue;
        }
        const Node& x0 = n5[1 - i6];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        const Node& p0 = n2[1 - i4];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x1 = n9[1 - i10];
            if (!n3[1 - i8].type().is_bv())
            {
              continue;
            }
            const Node& x2 = n3[1 - i8];
            // Bit-widths required by the rule.
            if (n11.type().bv_size() != x0.type().bv_size())
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = p0;
            vars[2] = x1;
            vars[3] = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_allones_equality_reverse(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_zero(size));
  Node t2         = rewriter.mk_node(Kind::EQUAL, {vars[0], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t3});
  Node t5         = rewriter.mk_node(Kind::EQUAL, {t4, vars[2]});
  Node t6         = rewriter.mk_node(Kind::AND, {t2, t5});
  Node t7         = rewriter.mk_node(Kind::AND, {vars[1], t6});
  return t7;
}

// (define-rule bvadd-all-ones-as-minus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_all_ones_as_minus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ASHR || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        if (!is_one(n7[1]))
        {
          continue;
        }
        const Node& x1 = n7[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_all_ones_as_minus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-all-ones-cancel-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvnot x2)))
//   (bvadd x0 x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_all_ones_cancel_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_one(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          const Node& x2 = n6[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_all_ones_cancel_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule bvadd-all-ones-equals-xor
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvxor x1 x2)))
//   (= (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_all_ones_equals_xor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n5[i6];
        const Node& x2 = n5[1 - i6];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_all_ones_equals_xor(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t2, t3});
  return t4;
}

// (define-rule bvadd-cancel-allones ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) x1))
//   (bvadd x1 (bvnot x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_allones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n8[0];
        const Node& x1 = n3[1 - i4];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_allones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  return t2;
}

// (define-rule bvadd-cancel-allones-and-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_allones_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ASHR || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      if (!is_one(n5[1]))
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_allones_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  return t3;
}

// (define-rule bvadd-cancel-allones-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_allones_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n8[i9];
          const Node& x2 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_allones_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-cancel-all-ones ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvadd x0 (bvadd (bvnot x1) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x1 = n9[0];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-cancel-all-ones-2 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvnot (bvadd x1 x2)) (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& n9 = n7[0];
        if (n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n9[i10];
          const Node& x2 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-cancel-all-ones-3 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x1 = n7[1 - i8];
          const Node& x2 = n5[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-cancel-all-ones-4 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))
//     (bvadd x0 (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n6[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[i9];
          const Node& n11 = n3[1 - i9];
          if (!is_one(n11))
          {
            continue;
          }
          if (n10 != x0)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_4(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-cancel-all-ones-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 x3)))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-all-ones-and-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd x0 x1) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_and_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n5[i7];
        const Node& x1 = n5[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            const Node& x3 = n6[1 - i8];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_and_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-all-ones-and-one-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x2 x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_and_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (!is_one(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_and_one_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-all-ones-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvashr x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!is_one(n2[1]))
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x1 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-cancel-all-ones-with-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//     (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_all_ones_with_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_all_ones_with_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-cancel-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//     x3)
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x2 = n9[i10];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complemented-summand
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0 (bvadd x1 (bvadd x2 (bvnot (bvadd x0 x3)))))
//   (bvadd x1 (bvadd x2 (bvnot x3))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complemented_summand(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x1 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x2 = n4[i5];
        const Node& n7 = n6[0];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x3 = n7[1 - i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complemented_summand(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  return t3;
}

// (define-rule bvadd-cancel-complement-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvadd x1 (@bv 1 (@bvsize x0))) (bvadd x2 x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n8[i11];
            const Node& x3 = n8[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complement-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complement-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) (bvadd x0 x2))
//   (bvnot (bvadd (bvnot x2) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& n7 = n5[0];
      if (n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[i9];
          if (n10 != x0)
          {
            continue;
          }
          const Node& x2 = n3[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_4(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvadd-cancel-complement-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd x1
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x2)
//         (bvadd x3 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x1 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n7[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n7[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complement-offset-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2))
//       (bvadd x3 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_offset_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n8[i9];
          const Node& x2 = n8[1 - i9];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n5[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n5[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_offset_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complement-offset-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 x1)
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_offset_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_offset_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-complement-offset-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_complement_offset_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n8[i11];
            const Node& x3 = n8[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_complement_offset_4(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-minus-one-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd x1 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3))
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            const Node& x3 = n7[1 - i8];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-minus-one-and-one-2 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_and_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ASHR || !is_one(n8))
        {
          continue;
        }
        if (!is_one(n7[1]))
        {
          continue;
        }
        const Node& x1 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_and_one_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-cancel-minus-one-and-one-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd
//         (bvashr x0 (@bv 1 (@bvsize x0)))
//         (bvadd x1 (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_and_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ASHR || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        if (!is_one(n7[1]))
        {
          continue;
        }
        const Node& x0 = n7[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_and_one_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-cancel-minus-one-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 x2)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n6[i9];
          const Node& x2 = n6[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-cancel-minus-one-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//       (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x1 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n5[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n5[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-minus-one-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-minus-one-plus-one-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_minus_one_plus_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_minus_one_plus_one_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-cancel-negated-zero ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_negated_zero(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n9[1]))
        {
          continue;
        }
        const Node& x1 = n9[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_negated_zero(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-cancel-negative-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_negative_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n6[i11];
            const Node& x3 = n6[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_negative_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-negative-one-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0))))
//         x2)
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_negative_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = n4[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_negative_one_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-cancel-neg-one-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_neg_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x0 = n8[i9];
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_neg_one_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-cancel-neg-one-and-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)))
//     x3)
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_neg_one_and_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x0 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x1 = n8[i11];
            const Node& x2 = n8[1 - i11];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_neg_one_and_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-offset ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x1 = n7[1 - i8];
          const Node& x2 = n5[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-cancel-offsets ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x2 = n10[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_offsets(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t2});
  return t4;
}

// (define-rule bvadd-cancel-ones ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n4[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvadd-cancel-one-minus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_one_minus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            const Node& x3 = n3[1 - i8];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_one_minus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-cancel-one-minus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_cancel_one_minus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n8[i11];
            const Node& x3 = n8[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_cancel_one_minus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-carry-constant-fold
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd x0 (bvnot x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvnot x1) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_carry_constant_fold(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n5[i7];
        const Node& x1 = n8[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_carry_constant_fold(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule bvadd-collapse-all-ones ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_collapse_all_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x1 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_collapse_all_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  return t2;
}

// (define-rule bvadd-combine-complemented-pair
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvadd x0 (bvadd x1 (bvadd x2 x3))) (bvadd x4 (@bv 1 (@bvsize x0))))
//   (bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x2 x3 x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_combine_complemented_pair(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x2 = n7[i8];
          const Node& x3 = n7[1 - i8];
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n3[1 - i9];
            if (!is_one(n10))
            {
              continue;
            }
            const Node& x4 = n3[i9];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_combine_complemented_pair(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, vars[2]});
  Node t6 = rewriter.mk_node(Kind::BV_ADD, {t5, vars[3]});
  Node t7 = rewriter.mk_node(Kind::BV_ADD, {t6, vars[4]});
  return t7;
}

// (define-rule bvadd-complemented-negation ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd x0
//     (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complemented_negation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvadd_complemented_negation(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  Node t5         = rewriter.mk_node(Kind::BV_NOT, {t4});
  return t5;
}

// (define-rule bvadd-complement-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd x1 (bvnot x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complement_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n3[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_complement_cancel(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  return t2;
}

// (define-rule bvadd-complement-equality-xor
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0 (bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2))
//   (= (bvnot (bvxor x0 x2)) (bvadd x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complement_equality_xor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_XOR)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (!is_ones(n6) || n7.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = n2[1 - i3];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_complement_equality_xor(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_XOR, {vars[0], vars[2]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::EQUAL, {t2, t4});
  return t5;
}

// (define-rule bvadd-complement-reassociate
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd x0 (bvnot x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x1 (bvnot (bvadd x0 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complement_reassociate(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n3[i5];
      const Node& x1 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x2 = n4[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_complement_reassociate(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  return t3;
}

// (define-rule bvadd-complement-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))
//   (bvadd x2 (bvnot (bvadd x0 x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complement_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& n9 = n7[0];
        if (n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          const Node& x2 = n3[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_complement_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  return t3;
}

// (define-rule bvadd-complement-sum-2 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvadd (bvnot x1) (bvnot x2)) (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_complement_sum_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_NOT || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_complement_sum_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-fold-minus-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (bvashr x1 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_fold_minus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n9[0];
        if (!is_one(n6[1]))
        {
          continue;
        }
        const Node& x1 = n6[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_fold_minus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule bvadd-fold-negated-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//     x2)
//   (bvadd x0 (bvadd (bvnot x1) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_fold_negated_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n5[i8];
          const Node& n10 = n5[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x1 = n9[0];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_fold_negated_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-inverse-rearrange ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0 (bvadd (bvadd x1 (bvnot x2)) x2))
//   (= (bvadd x0 (@bv 1 (@bvsize x0))) x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_inverse_rearrange(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n4[i5];
        const Node& x2 = n6[0];
        if (n2[1 - i3] != x2)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        vars[2] = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_inverse_rearrange(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[1]});
  return t3;
}

// (define-rule bvadd-minus-one-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        const Node& n9 = n6[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n6[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n9[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-minus-one-equality
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)
//   (= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n5[i6];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        const Node& x1 = n5[1 - i6];
        if (!node[1 - i1].type().is_bv())
        {
          continue;
        }
        const Node& x2 = node[1 - i1];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_equality(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t1, t3});
  return t4;
}

// (define-rule bvadd-minus-one-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (= x0 (bvadd x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::EQUAL, {vars[0], t1});
  return t2;
}

// (define-rule bvadd-minus-one-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//         x1)
//       x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x0 = n10[0];
          const Node& x1 = n5[1 - i6];
          const Node& x2 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-minus-one-plus-one-3 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_plus_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[i10];
          if (n11 != x0)
          {
            continue;
          }
          const Node& x1 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_plus_one_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-minus-one-plus-one-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvashr x2 (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_plus_one_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          if (!is_one(n8[1]))
          {
            continue;
          }
          const Node& x2 = n8[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_plus_one_4(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t2});
  return t4;
}

// (define-rule bvadd-minus-one-plus-one-5
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvand
//     (bvxor x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//     x3)
//   (bvand (bvxor x0 (bvadd x1 x2)) x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_plus_one_5(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x2 = n9[i10];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_plus_one_5(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-minus-one-subtraction
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (=
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//     x2)
//   (= (bvadd x0 (bvnot x1)) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_minus_one_subtraction(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i6];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x1 = n9[0];
          if (!node[1 - i1].type().is_bv())
          {
            continue;
          }
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_minus_one_subtraction(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::EQUAL, {t2, vars[2]});
  return t3;
}

// (define-rule bvadd-negated-shift-cancellation ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd x0
//       (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//     (bvashr x1 (@bv 1 (@bvsize x0))))
//   x0)
bool
match_bvadd_negated_shift_cancellation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n9[1]))
        {
          continue;
        }
        const Node& x1 = n9[0];
        if (!is_one(n3[1]))
        {
          continue;
        }
        if (n3[0] != x1)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_negated_shift_cancellation(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[0];
}

// (define-rule bvadd-negated-x1-and-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//     (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_negated_x1_and_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[i7];
        const Node& n9 = n3[1 - i7];
        if (n8.kind() != Kind::BV_NOT || !is_one(n9))
        {
          continue;
        }
        const Node& x1 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_negated_x1_and_arithmetic_shift(Rewriter& rewriter,
                                            const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule bvadd-negated-zero-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_negated_zero_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n6[i9];
          const Node& x2 = n6[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_negated_zero_cancel(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-negated-zero-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 x1)
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x2)
//       (bvadd x3 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_negated_zero_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n7[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n7[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_negated_zero_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-neg-one-and-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)))
//   (bvadd x0 (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10 != x0)
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  return t2;
}

// (define-rule bvadd-neg-one-and-one-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_and_one_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n6[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n3[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_and_one_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-neg-one-cancel ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvashr x1 (@bv 1 (@bvsize x0))))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        if (!is_one(n6[1]))
        {
          continue;
        }
        const Node& x1 = n6[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n3[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule bvadd-neg-one-cancel-2 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_cancel_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ASHR || !is_one(n8))
        {
          continue;
        }
        if (!is_one(n7[1]))
        {
          continue;
        }
        const Node& x1 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_cancel_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-neg-one-cancel-3 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     x2)
//   (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_cancel_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n5[i8];
          const Node& n10 = n5[1 - i8];
          if (n9.kind() != Kind::BV_ASHR || !is_one(n10))
          {
            continue;
          }
          if (!is_one(n9[1]))
          {
            continue;
          }
          const Node& x1 = n9[0];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_cancel_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-neg-one-plus-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n3[i6];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  return t1;
}

// (define-rule bvadd-neg-one-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvxor x0
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvxor x0 (bvadd x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[0], t1});
  return t2;
}

// (define-rule bvadd-neg-one-plus-one-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_plus_one_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n9[i10];
          const Node& x2 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_plus_one_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-neg-one-plus-one-cancellation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_plus_one_cancellation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_plus_one_cancellation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule bvadd-neg-one-plus-one-cancel-2 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//       x1)
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_neg_one_plus_one_cancel_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x0 = n8[0];
        const Node& x1 = n2[1 - i4];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_neg_one_plus_one_cancel_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  return t3;
}

// (define-rule bvadd-not-and-to-not-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvnot x0) (bvadd (@bv 1 (@bvsize x0)) (bvand (bvand x1 x2) x3)))
//   (bvnot (bvadd x0 (bvnot (bvand (bvand x1 x2) x3)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_and_to_not_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n8[i9];
          const Node& x2 = n8[1 - i9];
          const Node& x3 = n6[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_not_and_to_not_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {t1, vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  Node t5 = rewriter.mk_node(Kind::BV_NOT, {t4});
  return t5;
}

// (define-rule bvadd-not-complement-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd x0 (bvnot x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_complement_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      const Node& x1 = n5[0];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_not_complement_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-not-subtract-simplification ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd
//         (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) x0))
//         (@bv 1 (@bvsize x0)))
//       x1)
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvadd x1 (bvnot x0)) (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_subtract_simplification(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& n9 = n7[0];
        if (n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[i10];
          if (!is_ones(n11))
          {
            continue;
          }
          const Node& x0 = n9[1 - i10];
          const Node& x1 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_not_subtract_simplification(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule bvadd-not-sub-constant ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvnot x1))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x1 (bvadd (bvnot x0) (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_sub_constant(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (n9.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n7[i8];
        const Node& x1 = n9[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_not_sub_constant(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t3});
  return t4;
}

// (define-rule bvadd-not-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) (bvnot x2))
//   (bvnot (bvadd (bvadd x0 x1) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& n7 = n5[0];
      if (n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        const Node& x2 = n3[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_not_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvadd-not-sum-plus-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvnot (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_sum_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT || !is_one(n5))
      {
        continue;
      }
      const Node& n6 = n4[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_not_sum_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvadd-not-zero-collapse ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvadd (bvadd x1 x2) (bvnot x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_not_zero_collapse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n7[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_not_zero_collapse(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule bvadd-ones-and-increment-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0
//       (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))))
//   (bvadd x0 (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_ones_and_increment_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n9[1]))
        {
          continue;
        }
        const Node& x1 = n9[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_ones_and_increment_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvadd-one-as-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvxor (bvadd x0 x1) (bvadd x2 x3)) (bvadd x4 (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd (bvnot (bvxor (bvadd x0 x1) (bvadd x2 x3))) (bvnot x4))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_one_as_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_XOR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n5[i7];
        const Node& x1 = n5[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x2 = n6[i8];
          const Node& x3 = n6[1 - i8];
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n3[1 - i9];
            if (!is_one(n10))
            {
              continue;
            }
            const Node& x4 = n3[i9];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_one_as_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_XOR, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_NOT, {vars[4]});
  Node t6 = rewriter.mk_node(Kind::BV_ADD, {t4, t5});
  Node t7 = rewriter.mk_node(Kind::BV_NOT, {t6});
  return t7;
}

// (define-rule bvadd-one-as-complement-negation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3))))
//   (bvnot (bvadd (bvnot x0) (bvnot (bvadd x1 (bvadd x2 x3))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_one_as_complement_negation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x2 = n7[i8];
          const Node& x3 = n7[1 - i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_one_as_complement_negation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t1, t4});
  Node t6 = rewriter.mk_node(Kind::BV_NOT, {t5});
  return t6;
}

// (define-rule bvadd-one-as-negated-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))
//     (bvashr (bvadd x2 x3) (@bv 1 (@bvsize x0))))
//   (bvadd
//     (bvnot (bvadd (bvnot x0) (bvnot x1)))
//     (bvashr (bvadd x2 x3) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_one_as_negated_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        const Node& n8 = n3[0];
        if (n8.kind() != Kind::BV_ADD || !is_one(n3[1]))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x2 = n8[i9];
          const Node& x3 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_one_as_negated_complement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t6         = nm.mk_value(BitVector::mk_one(size));
  Node t7         = rewriter.mk_node(Kind::BV_ASHR, {t5, t6});
  Node t8         = rewriter.mk_node(Kind::BV_ADD, {t4, t7});
  return t8;
}

// (define-rule bvadd-one-complement-minus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_one_complement_minus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            const Node& x3 = n3[1 - i8];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_one_complement_minus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bvadd-one-equals-bitwise-difference
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvxor (bvand x1 x2) x1)))
//   (= (bvadd x0 (@bv 1 (@bvsize x0))) (bvand x1 (bvnot x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_one_equals_bitwise_difference(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x1 = n7[i8];
          const Node& x2 = n7[1 - i8];
          if (n5[1 - i6] != x1)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          vars[2] = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_one_equals_bitwise_difference(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_AND, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::EQUAL, {t2, t4});
  return t5;
}

// (define-rule bvadd-reassociate-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x0 (bvadd x2 x3)))
//   (bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x0 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_reassociate_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          if (n9 != x0)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_reassociate_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, vars[0]});
  Node t6 = rewriter.mk_node(Kind::BV_ADD, {t5, vars[2]});
  Node t7 = rewriter.mk_node(Kind::BV_ADD, {t6, vars[3]});
  return t7;
}

// (define-rule bvadd-reassociate-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvand x1 x2) x3))
//   (bvadd (bvnot (bvadd (bvnot x0) (bvnot x3))) (bvand x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvadd_reassociate_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x1 = n7[i8];
          const Node& x2 = n7[1 - i8];
          const Node& x3 = n3[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvadd_reassociate_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t6 = rewriter.mk_node(Kind::BV_ADD, {t4, t5});
  return t6;
}

// (define-rule bvadd-sub-cancellation ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x1)
//   x0)
bool
match_bvadd_sub_cancellation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (n6.kind() != Kind::BV_NOT || !is_one(n7))
        {
          continue;
        }
        const Node& x1 = n6[0];
        if (node[1 - i1] != x1)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvadd_sub_cancellation(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[0];
}

// (define-rule bvand-clear-bits ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvand x0 (bvand (bvnot (bvand x0 x1)) (bvnot x2)))
//   (bvand x0 (bvnot x1) (bvnot x2)))
bool
match_bvand_clear_bits(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n4[0];
      if (n6.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8 != x0)
        {
          continue;
        }
        const Node& x1 = n6[1 - i7];
        const Node& x2 = n5[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvand_clear_bits(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {vars[0], t1});
  Node t4 = rewriter.mk_node(Kind::BV_AND, {t3, t2});
  return t4;
}

// (define-rule bvand-distribute-inverted-factor
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvand x0 (bvand (bvnot (bvand (bvand x0 x1) x2)) x3))
//   (bvand x0 (bvand x3 (bvnot (bvand x1 x2)))))
bool
match_bvand_distribute_inverted_factor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n5 = n4[0];
      if (n5.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x1 = n7[1 - i8];
          const Node& x2 = n5[1 - i6];
          const Node& x3 = n2[1 - i3];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvand_distribute_inverted_factor(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {vars[3], t2});
  Node t4 = rewriter.mk_node(Kind::BV_AND, {vars[0], t3});
  return t4;
}

// (define-rule bvand-equality-idempotence
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (and (and p0 (= (bvand x0 x1) x2)) (= x0 x2))
//   (and p0 (= x0 x2) (= (bvand x0 (bvnot x1)) (@bv 0 (@bvsize x0)))))
bool
match_bvand_equality_idempotence(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      const Node& p0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x0 = n7[i8];
          const Node& x1 = n7[1 - i8];
          if (!n5[1 - i6].type().is_bv())
          {
            continue;
          }
          const Node& x2 = n5[1 - i6];
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n3[i9];
            const Node& n11 = n3[1 - i9];
            if (n10 != x0)
            {
              continue;
            }
            if (n11 != x2)
            {
              continue;
            }
            vars[0] = p0;
            vars[1] = x0;
            vars[2] = x1;
            vars[3] = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvand_equality_idempotence(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::EQUAL, {vars[1], vars[3]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_AND, {vars[1], t2});
  Node t4         = nm.mk_value(BitVector::mk_zero(size));
  Node t5         = rewriter.mk_node(Kind::EQUAL, {t3, t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t1});
  Node t7         = rewriter.mk_node(Kind::AND, {t6, t5});
  return t7;
}

// (define-rule bvand-mask-distribution ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvand (bvand x0 (bvnot (bvand x1 (bvnot x2)))) x1)
//   (bvand x0 x1 x2))
bool
match_bvand_mask_distribution(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      const Node& n5 = n4[0];
      if (n5.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        const Node& x2 = n7[0];
        if (node[1 - i1] != x1)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        vars[2] = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvand_mask_distribution(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {t1, vars[2]});
  return t2;
}

// (define-rule bvashr-cancel-additive-constants
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvashr_cancel_additive_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvashr_cancel_additive_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule bvashr-negated-difference ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvnot (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x1 (bvnot x0)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvashr_negated_difference(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_NOT || !is_one(node[1]))
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[1 - i3];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[i3];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_NOT || !is_one(n7))
      {
        continue;
      }
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvashr_negated_difference(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule bvnot-add-cancel-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvnot
//       (bvadd
//         (bvashr x0 (@bv 1 (@bvsize x0)))
//         (bvadd x1 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_cancel_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n4 = n3[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ASHR || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n7[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_cancel_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule bvnot-add-complement ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))))
//   (bvnot x1))
bool
match_bvnot_add_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x0 = n3[i5];
      const Node& x1 = n3[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        if (n7[0] != x0)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  return t1;
}

// (define-rule bvnot-add-complemented-and
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvnot (bvand x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvand x0 x1) (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_complemented_and(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_NOT || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n5 = n3[0];
    if (n5.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i6 = 0; i6 < 2; ++i6)
    {
      const Node& x0 = n5[i6];
      const Node& x1 = n5[1 - i6];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x2 = n4[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_complemented_and(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule bvnot-add-identity ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot x0)
//     (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_identity(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n7[1]))
      {
        continue;
      }
      const Node& x1 = n7[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_add_identity(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule bvnot-add-inverse-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd x0 (bvadd x1 (bvnot (bvadd x0 x2)))))
//   (bvnot (bvadd x1 (bvnot x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_inverse_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x1 = n3[i4];
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8 != x0)
        {
          continue;
        }
        const Node& x2 = n6[1 - i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_inverse_cancel(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvnot-add-mask-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd x0
//       (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvand x1 (@bv 1 (@bvsize x0)))))))
//   (bvadd (bvnot x0) (bvand x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_mask_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n7[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_mask_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_AND, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule bvnot-add-negated-subtrahend ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//   (bvadd x1 (bvnot x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_negated_subtrahend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& x1 = n5[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_add_negated_subtrahend(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  return t2;
}

// (define-rule bvnot-add-negated-subtrahend-2 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_negated_subtrahend_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_NOT || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x1 = n4[i5];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_add_negated_subtrahend_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  return t2;
}

// (define-rule bvnot-add-negated-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))) x2))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_negated_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_negated_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvnot-add-negation-collapse
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvnot x0) (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvnot (bvand x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_negation_collapse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_NOT || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_AND || !is_one(n7))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x1 = n6[i8];
        const Node& x2 = n6[1 - i8];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_negation_collapse(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvnot-add-normalize ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_normalize(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_add_normalize(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvnot-add-one-and ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd x0 (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot x0) (bvnot (bvand x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_one_and(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_AND || !is_one(n6))
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x1 = n5[i7];
        const Node& x2 = n5[1 - i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_one_and(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule bvnot-add-one-collapse ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (bvadd x0 (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 (bvand x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_one_collapse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (n8.kind() != Kind::BV_AND || !is_one(n9))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n8[i10];
          const Node& x2 = n8[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_add_one_collapse(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvnot-add-one-simplify
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) (bvadd x2 x3))
//   (bvadd (bvnot x0) (bvnot x1) x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_one_simplify(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x2 = n3[i9];
          const Node& x3 = n3[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_add_one_simplify(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, vars[3]});
  return t5;
}

// (define-rule bvnot-add-plus-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot x0) (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x1 = n3[i4];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_add_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule bvnot-add-split ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot x0) (bvnot (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_split(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x0 = n3[i5];
      const Node& n7 = n4[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n4[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x1 = n7[i8];
        const Node& x2 = n7[1 - i8];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_split(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::BV_NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t1, t5});
  return t6;
}

// (define-rule bvnot-add-successor ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_successor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n6[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n7[i10];
          const Node& x2 = n7[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_add_successor(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvnot-add-sum-complement ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//   (bvadd
//     (bvnot x0)
//     (bvnot (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_sum_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x0 = n3[i5];
      const Node& n7 = n4[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n4[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n7[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_sum_complement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t3, t2});
  Node t5         = rewriter.mk_node(Kind::BV_NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t1, t5});
  return t6;
}

// (define-rule bvnot-add-to-complement-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot (bvashr x0 (@bv 1 (@bvsize x0)))) (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_to_complement_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ASHR || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!is_one(n3[1]))
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x1 = n4[i5];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_add_to_complement_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t3, t4});
  return t5;
}

// (define-rule bvnot-add-xor ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2)))
//   (bvadd (bvnot x0) (bvnot (bvxor x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_xor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x1 = n4[i7];
        const Node& x2 = n4[1 - i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_add_xor(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule bvnot-add-zero-minus-one-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_add_zero_minus_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_ones(n3) || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n6[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n7[i10];
          const Node& x2 = n7[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_add_zero_minus_one_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule bvnot-allones-add-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2))
//   (not (= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_allones_add_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        const Node& x1 = n6[1 - i7];
        if (!n1[1 - i2].type().is_bv())
        {
          continue;
        }
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_allones_add_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t1, t3});
  Node t5         = rewriter.mk_node(Kind::NOT, {t4});
  return t5;
}

// (define-rule bvnot-incremented-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2)
//   (bvadd x2 (bvadd (bvnot x0) (bvnot x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_incremented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n5[i6];
        const Node& x2 = node[1 - i1];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_incremented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t3});
  return t4;
}

// (define-rule bvnot-minus-one-add ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//       (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_minus_one_add(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n7[1]))
      {
        continue;
      }
      const Node& x0 = n7[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n4[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n4[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_minus_one_add(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule bvnot-sum-collapse ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvnot (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_collapse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n4[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_collapse(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  return t2;
}

// (define-rule bvnot-sum-complements ((x0 ?BitVec))
//   (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)))
//   (bvadd x0 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_complements(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_ones(n3) || n4.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& x0 = n4[0];
    vars[0]        = x0;
    return true;
  }
  return false;
}

Node
build_bvnot_sum_complements(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  return t2;
}

// (define-rule bvnot-sum-difference ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2))
//   (bvadd (bvnot (bvadd x0 x2)) x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_difference(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_difference(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  return t3;
}

// (define-rule bvnot-sum-distribute
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0 (bvadd (bvnot (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))) x3))
//   (bvadd x0 x3 (bvnot x1) (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_distribute(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n5 = n4[0];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          const Node& x3 = n2[1 - i3];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_distribute(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[3]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, t2});
  return t5;
}

// (define-rule bvnot-sum-grouped-negations
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvnot (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x2 x3)))
//   (bvadd (bvnot (bvadd x0 x1)) (bvnot (bvadd x2 x3))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_grouped_negations(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x2 = n4[i9];
          const Node& x3 = n4[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_grouped_negations(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t2, t4});
  return t5;
}

// (define-rule bvnot-sum-with-increments
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot x0) (bvnot x1) (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_with_increments(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n4[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n4[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_with_increments(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t5 = rewriter.mk_node(Kind::BV_ADD, {t4, t3});
  return t5;
}

// (define-rule bvnot-sum-with-offset ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)))
//   (bvnot (bvadd (bvadd x0 x1) (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_sum_with_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[i7];
        const Node& n9 = n3[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n9[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_sum_with_offset(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule bvnot-zero-add-cancel ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//         (bvashr x1 (@bv 1 (@bvsize x0))))
//       x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x0 = n7[1 - i9];
          if (!is_one(n8[1]))
          {
            continue;
          }
          const Node& x1 = n8[0];
          const Node& x2 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvnot-zero-add-equality
//     ((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and (and p0 p1) (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))
//   (and (and p0 p1) (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& p0 = n2[i4];
      const Node& p1 = n2[1 - i4];
      const Node& n5 = n3[0];
      if (n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x0 = n7[1 - i8];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n5[1 - i6].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n5[1 - i6];
          vars[0]        = p0;
          vars[1]        = p1;
          vars[2]        = x0;
          vars[3]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_equality(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[2].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::AND, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {vars[2], t3});
  Node t5         = rewriter.mk_node(Kind::NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::AND, {t1, t5});
  return t6;
}

// (define-rule bvnot-zero-add-identity ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and p0 (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))
//   (and p0 (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_identity(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::NOT)
    {
      continue;
    }
    const Node& p0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n5[1 - i6];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        if (!n3[1 - i4].type().is_bv())
        {
          continue;
        }
        const Node& x1 = n3[1 - i4];
        vars[0]        = p0;
        vars[1]        = x0;
        vars[2]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_identity(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::NOT, {t3});
  Node t5         = rewriter.mk_node(Kind::AND, {vars[0], t4});
  return t5;
}

// (define-rule bvnot-zero-add-identity-2
//     ((x0 ?BitVec) (x1 ?BitVec) (p0 Bool) (x2 ?BitVec))
//   (and
//     (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)
//     (and p0 (= (bvnot (@bv 0 (@bvsize x0))) x2)))
//   (and p0
//     (and
//       (= (bvadd x1 (@bv 1 (@bvsize x0))) x0)
//       (= x2 (bvnot (@bv 0 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_identity_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::EQUAL || n3.kind() != Kind::AND)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n5[1 - i6];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        if (!n2[1 - i4].type().is_bv())
        {
          continue;
        }
        const Node& x1 = n2[1 - i4];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[1 - i8];
          if (n9.kind() != Kind::EQUAL)
          {
            continue;
          }
          const Node& p0 = n3[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            if (!n9[1 - i10].type().is_bv())
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            // Bit-widths required by the rule.
            if (n11.type().bv_size() != x0.type().bv_size())
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = p0;
            vars[3] = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_identity_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[0]});
  Node t4         = nm.mk_value(BitVector::mk_ones(size));
  Node t5         = rewriter.mk_node(Kind::EQUAL, {vars[3], t4});
  Node t6         = rewriter.mk_node(Kind::AND, {t3, t5});
  Node t7         = rewriter.mk_node(Kind::AND, {vars[2], t6});
  return t7;
}

// (define-rule bvnot-zero-add-increment
//     ((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and (and p0 p1) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//   (and p0 (and p1 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_increment(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& p0 = n2[i4];
      const Node& p1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (!is_ones(n8))
          {
            continue;
          }
          const Node& x0 = n6[1 - i7];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n3[1 - i5].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n3[1 - i5];
          vars[0]        = p0;
          vars[1]        = p1;
          vars[2]        = x0;
          vars[3]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_increment(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[2].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::AND, {vars[0], t4});
  return t5;
}

// (define-rule bvnot-zero-add-inverse ((x0 ?BitVec) (x1 ?BitVec))
//   (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//   (not (= (bvadd x1 (@bv 1 (@bvsize x0))) x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_inverse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n3[1 - i4];
      // The result is not in normal form for bit-width 1.
      if (x0.type().bv_size() < 2)
      {
        return false;
      }
      if (!n1[1 - i2].type().is_bv())
      {
        continue;
      }
      const Node& x1 = n1[1 - i2];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bvnot_zero_add_inverse(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[0]});
  Node t4         = rewriter.mk_node(Kind::NOT, {t3});
  return t4;
}

// (define-rule bvnot-zero-add-invert
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))
//   (and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) (not p1))
//   (and p0 (and (not p1) (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_invert(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      const Node& p0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x0 = n7[1 - i8];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n5[1 - i6].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n5[1 - i6];
          const Node& p1 = n3[0];
          vars[0]        = p0;
          vars[1]        = x0;
          vars[2]        = x1;
          vars[3]        = p1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_invert(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::NOT, {vars[3]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::AND, {t1, t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t5});
  return t6;
}

// (define-rule bvnot-zero-add-one-cancel ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvashr x1 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_one_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        if (!is_one(n6[1]))
        {
          continue;
        }
        const Node& x1 = n6[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_one_cancel(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule bvnot-zero-add-one-reassociate
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (and p0 (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)))
//   (and p0 (not (= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_one_reassociate(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::NOT)
    {
      continue;
    }
    const Node& p0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x0 = n8[i9];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          const Node& x1 = n8[1 - i9];
          if (!n3[1 - i4].type().is_bv())
          {
            continue;
          }
          const Node& x2 = n3[1 - i4];
          vars[0]        = p0;
          vars[1]        = x0;
          vars[2]        = x1;
          vars[3]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_one_reassociate(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t1, t3});
  Node t5         = rewriter.mk_node(Kind::NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t5});
  return t6;
}

// (define-rule bvnot-zero-add-reverse
//     ((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and p0 (not (and p1 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))))
//   (and p0 (not (and p1 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_add_reverse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::NOT)
    {
      continue;
    }
    const Node& p0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::AND)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      const Node& p1 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x0 = n7[1 - i8];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n5[1 - i6].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n5[1 - i6];
          vars[0]        = p0;
          vars[1]        = p1;
          vars[2]        = x0;
          vars[3]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_add_reverse(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[2].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t5});
  return t6;
}

// (define-rule bvnot-zero-plus-increment-inverse
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//   (and p0 (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_plus_increment_inverse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::EQUAL)
    {
      continue;
    }
    const Node& p0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        if (!is_ones(n6))
        {
          continue;
        }
        const Node& x0 = n4[1 - i5];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        if (!n2[1 - i3].type().is_bv())
        {
          continue;
        }
        const Node& x1 = n2[1 - i3];
        vars[0]        = p0;
        vars[1]        = x0;
        vars[2]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_plus_increment_inverse(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[0], t3});
  return t4;
}

// (define-rule bvnot-zero-plus-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        const Node& n9 = n6[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n6[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n9[i10];
          const Node& x2 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule bvnot-zero-plus-x-equality
//     ((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (not (and (and p0 p1) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))
//   (not (and p0 p1 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_plus_x_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::AND || n4.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& p0 = n3[i5];
      const Node& p1 = n3[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x0 = n7[1 - i8];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n4[1 - i6].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n4[1 - i6];
          vars[0]        = p0;
          vars[1]        = p1;
          vars[2]        = x0;
          vars[3]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_plus_x_equality(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[2].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[3], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[0], vars[1]});
  Node t5         = rewriter.mk_node(Kind::AND, {t4, t3});
  Node t6         = rewriter.mk_node(Kind::NOT, {t5});
  return t6;
}

// (define-rule bvnot-zero-plus-x-equality-2
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))
//   (and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) p1)
//   (and p0 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))) p1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_plus_x_equality_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::AND)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::EQUAL)
      {
        continue;
      }
      const Node& p0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (!is_ones(n8))
          {
            continue;
          }
          const Node& x0 = n6[1 - i7];
          // The result is not in normal form for bit-width 1.
          if (x0.type().bv_size() < 2)
          {
            return false;
          }
          if (!n4[1 - i5].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n4[1 - i5];
          const Node& p1 = node[1 - i1];
          vars[0]        = p0;
          vars[1]        = x0;
          vars[2]        = x1;
          vars[3]        = p1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_plus_x_equality_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[0], t3});
  Node t5         = rewriter.mk_node(Kind::AND, {t4, vars[3]});
  return t5;
}

// (define-rule bvnot-zero-plus-x-equals-successor
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool) (p2 Bool))
//   (and (and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) p1) p2)
//   (and p0 (and p1 (and p2 (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bvnot_zero_plus_x_equals_successor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::AND)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::AND)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::EQUAL)
        {
          continue;
        }
        const Node& p0 = n4[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (n8.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (!is_ones(n10))
            {
              continue;
            }
            const Node& x0 = n8[1 - i9];
            // The result is not in normal form for bit-width 1.
            if (x0.type().bv_size() < 2)
            {
              return false;
            }
            if (!n6[1 - i7].type().is_bv())
            {
              continue;
            }
            const Node& x1 = n6[1 - i7];
            const Node& p1 = n2[1 - i3];
            const Node& p2 = node[1 - i1];
            vars[0]        = p0;
            vars[1]        = x0;
            vars[2]        = x1;
            vars[3]        = p1;
            vars[4]        = p2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bvnot_zero_plus_x_equals_successor(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[4], t3});
  Node t5         = rewriter.mk_node(Kind::AND, {vars[3], t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t5});
  return t6;
}

// (define-rule bv-add-all-ones-cancel
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)) x3))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_add_all_ones_cancel(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x0 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x1 = n8[i11];
            const Node& x2 = n8[1 - i11];
            const Node& x3 = n3[1 - i4];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bv_add_all_ones_cancel(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule bv-add-minus-one-offset ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvxor
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2))
//     x0)
//   (bvxor (bvadd x0 (bvadd x1 x2)) x0))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_add_minus_one_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_one(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x0 = n10[i11];
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n5[1 - i6];
            if (node[1 - i1] != x0)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bv_add_minus_one_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_XOR, {t2, vars[0]});
  return t3;
}

// (define-rule bv-complement-plus-x-to-increment
//     ((p0 Bool) (p1 Bool) (p2 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and (and (and p0 p1) p2) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//   (and p0 p1 p2 (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_complement_plus_x_to_increment(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& p0 = n5[i6];
        const Node& p1 = n5[1 - i6];
        const Node& p2 = n2[1 - i4];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (!is_ones(n10))
            {
              continue;
            }
            const Node& x0 = n8[1 - i9];
            // The result is not in normal form for bit-width 1.
            if (x0.type().bv_size() < 2)
            {
              return false;
            }
            if (!n3[1 - i7].type().is_bv())
            {
              continue;
            }
            const Node& x1 = n3[1 - i7];
            vars[0]        = p0;
            vars[1]        = p1;
            vars[2]        = p2;
            vars[3]        = x0;
            vars[4]        = x1;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_bv_complement_plus_x_to_increment(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[3].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[4], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {vars[3], t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[0], vars[1]});
  Node t5         = rewriter.mk_node(Kind::AND, {t4, vars[2]});
  Node t6         = rewriter.mk_node(Kind::AND, {t5, t3});
  return t6;
}

// (define-rule bv-negated-sum-expression ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and p0 (bvslt (@bv 0 (@bvsize x0)) (bvadd x0 (bvnot (bvadd x0 x1)))))
//   (and p0 (bvslt (@bv 0 (@bvsize x0)) (bvnot x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_negated_sum_expression(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_SLT)
    {
      continue;
    }
    const Node& p0 = node[i1];
    const Node& n3 = n2[1];
    if (!is_zero(n2[0]) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      // The result is not in normal form for bit-width 1.
      if (x0.type().bv_size() < 2)
      {
        return false;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8 != x0)
        {
          continue;
        }
        const Node& x1 = n6[1 - i7];
        vars[0]        = p0;
        vars[1]        = x0;
        vars[2]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bv_negated_sum_expression(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_zero(size));
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_SLT, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[0], t3});
  return t4;
}

// (define-rule bv-sub-increment-equivalence
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and (not p0) (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))
//   (and (not p0) (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_sub_increment_equivalence(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::NOT || n3.kind() != Kind::NOT)
    {
      continue;
    }
    const Node& p0 = n2[0];
    const Node& n4 = n3[0];
    if (n4.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n6[1 - i7];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        if (!n4[1 - i5].type().is_bv())
        {
          continue;
        }
        const Node& x1 = n4[1 - i5];
        vars[0]        = p0;
        vars[1]        = x0;
        vars[2]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_bv_sub_increment_equivalence(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[1].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {vars[1], t3});
  Node t5         = rewriter.mk_node(Kind::NOT, {t4});
  Node t6         = rewriter.mk_node(Kind::AND, {t1, t5});
  return t6;
}

// (define-rule bv-sub-via-negated-operands ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd x1 (bvnot x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_bv_sub_via_negated_operands(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT || !is_one(n5))
      {
        continue;
      }
      const Node& x1 = n4[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_bv_sub_via_negated_operands(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule cancelled-addend ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd x1 (bvnot (bvadd x0 x2))))
//   (bvadd x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancelled_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x1 = n2[i3];
      const Node& n5 = n4[0];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7 != x0)
        {
          continue;
        }
        const Node& x2 = n5[1 - i6];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancelled_addend(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  return t2;
}

// (define-rule cancel-additive-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))
//   (bvnot (bvadd x1 (bvnot x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (n6.kind() != Kind::BV_NOT || !is_one(n7))
        {
          continue;
        }
        const Node& n8 = n6[0];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10 != x0)
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n2[1 - i3];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_additive_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule cancel-additive-constants
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_additive_constants(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule cancel-additive-constants-before-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_constants_before_arithmetic_shift(const Node& node,
                                                        Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x0 = n3[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n4[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_additive_constants_before_arithmetic_shift(Rewriter& rewriter,
                                                        const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule cancel-additive-inverses-signed-lt
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvslt (bvadd (bvadd x0 (bvnot x1)) (bvadd x1 (@bv 1 (@bvsize x0)))) x2)
//   (bvslt x0 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_inverses_signed_lt(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_SLT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[1 - i5];
      if (n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n3[i5];
      // The result is not in normal form for bit-width 1.
      if (x0.type().bv_size() < 2)
      {
        return false;
      }
      const Node& x1 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (!is_one(n9))
        {
          continue;
        }
        if (n8 != x1)
        {
          continue;
        }
        const Node& x2 = node[1];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_additive_inverses_signed_lt(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_SLT, {vars[0], vars[2]});
  return t1;
}

// (define-rule cancel-additive-negation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))) x2))
//   (bvadd x0 x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_negation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          const Node& n9 = n6[1 - i7];
          if (n8.kind() != Kind::BV_NOT || !is_one(n9))
          {
            continue;
          }
          const Node& x2 = n8[0];
          if (n2[1 - i3] != x2)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          vars[2] = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_additive_negation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  return t1;
}

// (define-rule cancel-additive-ones ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_additive_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_additive_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule cancel-add-and-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvnot (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvnot (bvadd x1 (bvnot x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_add_and_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& n6 = n4[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8 != x0)
        {
          continue;
        }
        const Node& x1 = n6[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n5[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n5[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_add_and_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule cancel-add-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (= x0 (bvadd (bvadd x1 x2) (bvadd x3 (bvnot (bvadd x1 x2)))))
//   (= (bvadd x0 (@bv 1 (@bvsize x0))) x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_add_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n4[i6];
        const Node& x2 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[1 - i7];
          if (n8.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x3 = n5[i7];
          const Node& n9 = n8[0];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            const Node& n12 = n9[1 - i10];
            if (n11 != x1)
            {
              continue;
            }
            if (n12 != x2)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = x2;
            vars[3] = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_add_complement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-add-inverse ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x1))
//   (bvnot x0))
bool
match_cancel_add_inverse(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x1 = n7[0];
        if (n1[1 - i2] != x1)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_add_inverse(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  return t1;
}

// (define-rule cancel-add-one-and-all-ones
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 x3))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_add_one_and_all_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_add_one_and_all_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-add-one-from-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvnot (bvadd x0 x1)) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_add_one_from_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          const Node& x2 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_add_one_from_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule cancel-all-ones-addend ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0))) x2))
//   (bvadd x0 (bvnot x1) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || !is_one(n8))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (n10.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x0 = n7[i9];
          const Node& x1 = n10[0];
          const Node& x2 = n3[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_addend(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule cancel-all-ones-addends ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[i11];
            if (!is_ones(n12))
            {
              continue;
            }
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n6[1 - i9];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_addends(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule cancel-all-ones-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n3[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-all-ones-and-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0 (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_and_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n7[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_and_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule cancel-all-ones-and-one-3 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//       (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_and_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n9[1]))
        {
          continue;
        }
        const Node& x0 = n9[0];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n6[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n6[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_and_one_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule cancel-all-ones-offset ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvashr x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!is_one(n2[1]))
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_offset(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule cancel-all-ones-offset-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2))
//     x3)
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_offset_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_one(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x0 = n10[i11];
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n5[1 - i6];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_offset_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-all-ones-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0))))
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x1 = n8[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n5[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n5[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule cancel-all-ones-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2)) x3)
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_all_ones_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x1 = n10[i11];
            const Node& x2 = n10[1 - i11];
            const Node& x3 = n4[1 - i6];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_all_ones_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-bv-negated-zero-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2)))
//     x3)
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_bv_negated_zero_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n5[i8];
          const Node& n10 = n5[1 - i8];
          if (!is_one(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x1 = n10[i11];
            const Node& x2 = n10[1 - i11];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_bv_negated_zero_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-complemented-addend ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//     (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//   (bvadd (bvadd x0 x1) (bvadd (bvnot x1) (@bv 2 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_complemented_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          if (n9[0] != x1)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_complemented_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = nm.mk_value(BitVector::from_si(size, 2, true));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t1, t4});
  return t5;
}

// (define-rule cancel-complemented-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))
//     (bvadd x2 (bvnot (bvadd x0 x1))))
//   x2)
bool
match_cancel_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n3[1 - i8];
          if (n9.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x2  = n3[i8];
          const Node& n10 = n9[0];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[i11];
            const Node& n13 = n10[1 - i11];
            if (n12 != x0)
            {
              continue;
            }
            if (n13 != x1)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[2];
}

// (define-rule cancel-complemented-zero-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_complemented_zero_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_complemented_zero_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-complement-addend
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (not (= x0 (bvadd (bvadd x1 (bvnot x2)) x2)))
//   (not (= (bvadd x0 (@bv 1 (@bvsize x0))) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_complement_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!n1[i2].type().is_bv())
    {
      continue;
    }
    const Node& x0 = n1[i2];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        const Node& x2 = n7[0];
        if (n3[1 - i4] != x2)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        vars[2] = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_complement_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::NOT, {t3});
  return t4;
}

// (define-rule cancel-complement-increment
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))) x2)
//   (bvadd x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_complement_increment(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n4[i6];
        const Node& x1 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[i7];
          const Node& n9 = n5[1 - i7];
          if (n8.kind() != Kind::BV_NOT || !is_one(n9))
          {
            continue;
          }
          if (n8[0] != x0)
          {
            continue;
          }
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_complement_increment(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  return t1;
}

// (define-rule cancel-minus-one-and-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd
//         (bvashr x0 (@bv 1 (@bvsize x0)))
//         (bvadd x1 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_ones(n3) || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ASHR || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n7[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule cancel-minus-one-and-plus-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_and_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x1 = n5[i6];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_and_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  return t1;
}

// (define-rule cancel-minus-one-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2) x3))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x0 = n10[i11];
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n5[1 - i6];
            const Node& x3 = n3[1 - i4];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-minus-one-offset-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 (bvadd x2 x3))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_offset_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n6[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_offset_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-minus-one-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))
//       x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          const Node& x2 = n2[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule cancel-minus-one-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3)))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n10[i11];
            const Node& x3 = n10[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-minus-one-plus-one-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_minus_one_plus_one_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_ones(n3) || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n6[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n7[i10];
          const Node& x2 = n7[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_minus_one_plus_one_3(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule cancel-modular-offsets ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_modular_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x0 = n8[0];
        const Node& x1 = n6[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n3[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n3[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_modular_offsets(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule cancel-negated-addend ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvashr x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//   (bvadd x1 (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negated_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ASHR || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!is_one(n3[1]))
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_NOT || !is_one(n7))
      {
        continue;
      }
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_cancel_negated_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t3});
  return t4;
}

// (define-rule cancel-negated-addend-2 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvadd x1 (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))) x2))
//   (bvadd x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negated_addend_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          const Node& n9 = n6[1 - i7];
          if (n8.kind() != Kind::BV_NOT || !is_one(n9))
          {
            continue;
          }
          if (n8[0] != x0)
          {
            continue;
          }
          const Node& x2 = n2[1 - i3];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_negated_addend_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  return t1;
}

// (define-rule cancel-negated-x0 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvnot x0) (@bv 1 (@bvsize x0))) (bvadd x1 (bvadd x0 x2)))
//   (bvadd x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negated_x0(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10 != x0)
          {
            continue;
          }
          const Node& x2 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_negated_x0(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  return t1;
}

// (define-rule cancel-negated-zero-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//     x3)
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negated_zero_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[1 - i6];
        if (!is_one(n7))
        {
          continue;
        }
        const Node& x0 = n4[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n5[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x1 = n9[1 - i10];
            const Node& x2 = n5[1 - i8];
            const Node& x3 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_negated_zero_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-negative-one-and-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd x1 (bvashr x0 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negative_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n6[1]))
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n3[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_negative_one_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  return t3;
}

// (define-rule cancel-negative-one-offset ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//   (bvadd x0 x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_negative_one_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n5[1 - i6];
        const Node& x1 = n3[1 - i4];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_negative_one_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  return t1;
}

// (define-rule cancel-nested-add
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0 (bvadd x1 (bvadd x2 (bvnot (bvadd x1 x3)))))
//   (bvadd x0 x2 (bvnot x3)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_nested_add(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x1 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x2 = n4[i5];
        const Node& n7 = n6[0];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9 != x1)
          {
            continue;
          }
          const Node& x3 = n7[1 - i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_nested_add(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule cancel-not-zero-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) x3)
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_not_zero_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x1 = n9[1 - i10];
            const Node& x2 = n7[1 - i8];
            const Node& x3 = n2[1 - i4];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_cancel_not_zero_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule cancel-one-minus ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_one_minus(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x0 = n8[i9];
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n3[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_one_minus(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule cancel-one-plus-all-ones
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_one_plus_all_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x1 = n7[1 - i8];
          const Node& x2 = n3[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_one_plus_all_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule cancel-shifted-addend ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvashr x0 (@bv 1 (@bvsize x0)))
//     (bvadd x1 (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x2))))
//   (bvadd x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_shifted_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!is_one(n2[1]))
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x1 = n3[i4];
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        if (n8[0] != x0)
        {
          continue;
        }
        const Node& x2 = n6[1 - i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_shifted_addend(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  return t2;
}

// (define-rule cancel-shift-and-complement ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)
//     (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))
//   x1)
bool
match_cancel_shift_and_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n5[1]))
      {
        continue;
      }
      const Node& x0 = n5[0];
      const Node& x1 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n9[1]))
        {
          continue;
        }
        if (n9[0] != x0)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_cancel_shift_and_complement(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  return vars[1];
}

// (define-rule cancel-xor-complement-offset
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (bvadd x1 (bvnot x0)) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_cancel_xor_complement_offset(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[1 - i6];
        if (n7.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n4[i6];
        if (n7[0] != x0)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n5[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n5[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_cancel_xor_complement_offset(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  return t1;
}

// (define-rule carry-increment-add-complements
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))
//       (@bv 1 (@bvsize x0))))
//   (bvadd
//     (bvnot (bvadd (bvnot x0) (bvnot x1)))
//     (bvnot (bvadd (bvnot x2) (bvnot x3)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_carry_increment_add_complements(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_carry_increment_add_complements(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t6 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t7 = rewriter.mk_node(Kind::BV_ADD, {t5, t6});
  Node t8 = rewriter.mk_node(Kind::BV_NOT, {t7});
  Node t9 = rewriter.mk_node(Kind::BV_ADD, {t4, t8});
  return t9;
}

// (define-rule collapse-additive-constants
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_additive_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n6[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n6[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_collapse_additive_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule collapse-additive-constants-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_additive_constants_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n5[i7];
        const Node& x1 = n5[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n6[i8];
          const Node& n10 = n6[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x2 = n9[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_additive_constants_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule collapse-all-ones-addition ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_all_ones_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_all_ones_addition(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule collapse-complemented-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 (bvnot x1)) (bvnot x2)))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complemented_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n5[i7];
        const Node& x1 = n8[0];
        const Node& x2 = n6[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_collapse_complemented_addends(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule collapse-complemented-addends-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (bvadd x1 (@bv 1 (@bvsize x0))))
//     x2)
//   (bvadd x1 (bvnot x0) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complemented_addends_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n8[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n5[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n5[i9];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complemented_addends_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule collapse-complemented-addends-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x2 (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complemented_addends_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = n5[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complemented_addends_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule collapse-complemented-addends-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//     (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvadd x1 x2) (bvnot x0)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complemented_addends_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n6[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complemented_addends_4(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule collapse-complemented-zero-addend
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complemented_zero_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || !is_one(n8))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n10[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complemented_zero_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule collapse-complement-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd x0 (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complement_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[1 - i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x2 = n7[i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n9[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complement_and_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule collapse-complement-subtraction
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2))
//   (bvadd x0 (bvnot x1) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_complement_subtraction(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x1 = n9[0];
          const Node& x2 = n3[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_complement_subtraction(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule collapse-minus-one-addends-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2 (@bv (- 0 2) (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_minus_one_addends_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x0 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n5[i8];
          const Node& n10 = n5[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_minus_one_addends_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = nm.mk_value(BitVector::from_si(size, -2, true));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, vars[2]});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t5, t3});
  return t6;
}

// (define-rule collapse-minus-one-addition ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvashr
//         (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//         (@bv 1 (@bvsize x0))))
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd x1
//     (bvashr
//       (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_minus_one_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n6[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n7[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n9[i10];
          for (size_t i12 = 0; i12 < 2; ++i12)
          {
            const Node& n13 = n3[i12];
            const Node& n14 = n3[1 - i12];
            if (!is_one(n14))
            {
              continue;
            }
            if (n13 != x1)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_collapse_minus_one_addition(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t3, t1});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t4});
  return t5;
}

// (define-rule collapse-not-zero-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_not_zero_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x1 = n4[1 - i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n5[1 - i8];
          if (!is_one(n9))
          {
            continue;
          }
          const Node& x2 = n5[i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_collapse_not_zero_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  return t2;
}

// (define-rule collapse-ones-complement-addition
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_collapse_ones_complement_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n8[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n8[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_collapse_ones_complement_addition(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-added-constants ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd
//       (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvadd x0 x1) (bvadd x2 (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_added_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n6[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n6[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_added_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule combine-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 x1)
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3)))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (!is_one(n6) || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            if (!is_ones(n11))
            {
              continue;
            }
            const Node& x2 = n9[1 - i10];
            const Node& x3 = n7[1 - i8];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule combine-addends-2 ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))
//       x2)
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || !is_one(n8))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x0 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x1 = n10[i11];
            const Node& x2 = n2[1 - i4];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-addends-and-constants
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))
//       (bvadd x2 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends_and_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        const Node& n9 = n5[1 - i7];
        if (!is_one(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n6[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n6[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends_and_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-addends-and-constants-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0))) (@bv (- 2) (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends_and_constants_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x2 = n10[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends_and_constants_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[2], t1});
  Node t3         = nm.mk_value(BitVector::from_si(size, -2, true));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, t2});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t5, t3});
  return t6;
}

// (define-rule combine-addends-before-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd
//         (bvadd x0 (@bv 1 (@bvsize x0)))
//         (bvadd x1 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 (@bv 3 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends_before_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_one(n3) || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n6[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n7[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n7[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends_before_arithmetic_shift(Rewriter& rewriter,
                                              const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  Node t4         = nm.mk_value(BitVector::mk_one(size));
  Node t5         = rewriter.mk_node(Kind::BV_ASHR, {t3, t4});
  return t5;
}

// (define-rule combine-addends-before-arithmetic-shift-2
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd (bvadd x0 x1) x0) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_addends_before_arithmetic_shift_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        if (n8 != x0)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n9[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_addends_before_arithmetic_shift_2(Rewriter& rewriter,
                                                const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[0]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule combine-additive-constants
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd (bvadd x1 (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_additive_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n8[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n8[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_additive_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-additive-constants-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_additive_constants_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[i11];
            if (!is_ones(n12))
            {
              continue;
            }
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n8[1 - i9];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_additive_constants_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-all-ones-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x0
//     (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))
//     (bvnot (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_all_ones_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n9[i10];
          const Node& x2 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_all_ones_addends(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = nm.mk_value(BitVector::from_si(size, -2, true));
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t5, t4});
  return t6;
}

// (define-rule combine-bvadd-constants ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))
//     (bvadd x2 (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_bvadd_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || !is_one(n6))
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n3[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n3[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_bvadd_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-canceling-offsets ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_canceling_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        if (n7 != x0)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_canceling_offsets(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  return t2;
}

// (define-rule combine-complemented-addends-2 ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x1))
//   (bvnot (bvadd (bvnot x0) (bvnot x1) (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_complemented_addends_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        if (!is_ones(n7))
        {
          continue;
        }
        const Node& x1 = n3[1 - i6];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_combine_complemented_addends_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, t3});
  Node t6         = rewriter.mk_node(Kind::BV_NOT, {t5});
  return t6;
}

// (define-rule combine-complemented-addends-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0))) (bvnot x2))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_complemented_addends_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || !is_one(n6))
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n5[i7];
        const Node& x1 = n8[0];
        const Node& x2 = n3[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_combine_complemented_addends_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule combine-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2)
//   (bvadd (bvnot (bvadd x0 x1)) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_NOT || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[0];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = node[1 - i1];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_combine_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule combine-constant-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd
//         (bvadd x1 (@bv 1 (@bvsize x0)))
//         (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_constant_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n8[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n8[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_constant_addends(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule combine-duplicate-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd (bvadd x2 (@bv 1 (@bvsize x0))) (bvadd x0 x1)))
//   (bvadd (bvadd x0 x1) (bvadd (bvadd x0 x1) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_duplicate_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (n9.kind() != Kind::BV_ADD || n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n9[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n9[i11];
            for (size_t i13 = 0; i13 < 2; ++i13)
            {
              const Node& n14 = n10[i13];
              const Node& n15 = n10[1 - i13];
              if (n14 != x0)
              {
                continue;
              }
              if (n15 != x1)
              {
                continue;
              }
              vars[0] = x0;
              vars[1] = x1;
              vars[2] = x2;
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_duplicate_addends(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule combine-increment-and-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2))
//   (bvadd x0 x2 (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_increment_and_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (!is_ones(n9) || n10.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = n3[1 - i6];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_increment_and_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule combine-nested-adds ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_nested_adds(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_combine_nested_adds(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule combine-offset-additions
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_combine_offset_additions(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n8[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n8[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_combine_offset_additions(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule complemented-incremented-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_complemented_incremented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_complemented_incremented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  return t2;
}

// (define-rule complemented-incremented-sum-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvnot (bvadd x0 (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_complemented_incremented_sum_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n4 = n3[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_complemented_incremented_sum_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule complemented-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n5[0];
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  return t2;
}

// (define-rule complemented-sum-negation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvnot (bvadd x0 x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_complemented_sum_negation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x0 = n4[i5];
      const Node& x1 = n4[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_complemented_sum_negation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule complemented-sum-to-offset-subtraction
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) x1))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvadd (bvnot x1) (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_complemented_sum_to_offset_subtraction(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (!is_ones(n8) || n9.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x0 = n9[0];
        const Node& x1 = n4[1 - i5];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_complemented_sum_to_offset_subtraction(Rewriter& rewriter,
                                             const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule contradictory-boolean-conjunction
//     ((p0 Bool) (x0 ?BitVec) (p1 Bool))
//   (and (not p0) (and (= (@bv 0 (@bvsize x0)) x0) (and p0 p1)))
//   false)
bool
match_contradictory_boolean_conjunction(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::NOT || n3.kind() != Kind::AND)
    {
      continue;
    }
    const Node& p0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::EQUAL || n6.kind() != Kind::AND)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_zero(n8))
        {
          continue;
        }
        if (!n5[1 - i7].type().is_bv())
        {
          continue;
        }
        const Node& x0 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[i9];
          if (n10 != p0)
          {
            continue;
          }
          const Node& p1 = n6[1 - i9];
          vars[0]        = p0;
          vars[1]        = x0;
          vars[2]        = p1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_contradictory_boolean_conjunction(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  (void) vars;
  NodeManager& nm = rewriter.nm();
  return nm.mk_value(false);
}

// (define-rule contradictory-boolean-conjunction-2
//     ((p0 Bool) (x0 ?BitVec) (p1 Bool))
//   (and (not p0) (and (and (= (@bv 0 (@bvsize x0)) x0) p0) p1))
//   false)
bool
match_contradictory_boolean_conjunction_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::NOT || n3.kind() != Kind::AND)
    {
      continue;
    }
    const Node& p0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::EQUAL)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_zero(n10))
          {
            continue;
          }
          if (!n7[1 - i9].type().is_bv())
          {
            continue;
          }
          const Node& x0 = n7[1 - i9];
          if (n8 != p0)
          {
            continue;
          }
          const Node& p1 = n3[1 - i4];
          vars[0]        = p0;
          vars[1]        = x0;
          vars[2]        = p1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_contradictory_boolean_conjunction_2(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  (void) vars;
  NodeManager& nm = rewriter.nm();
  return nm.mk_value(false);
}

// (define-rule contradictory-equality
//     ((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))
//   (and (and (and p0 (not (= x0 x1))) p1) (= x0 x1))
//   false)
bool
match_contradictory_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::AND || n3.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[1 - i6];
        if (n7.kind() != Kind::NOT)
        {
          continue;
        }
        const Node& p0 = n5[i6];
        const Node& n8 = n7[0];
        if (n8.kind() != Kind::EQUAL)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          if (!n8[i9].type().is_bv())
          {
            continue;
          }
          const Node& x0 = n8[i9];
          if (!n8[1 - i9].type().is_bv())
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& p1 = n2[1 - i4];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n3[i10];
            const Node& n12 = n3[1 - i10];
            if (n11 != x0)
            {
              continue;
            }
            if (n12 != x1)
            {
              continue;
            }
            vars[0] = p0;
            vars[1] = x0;
            vars[2] = x1;
            vars[3] = p1;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_contradictory_equality(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  (void) vars;
  NodeManager& nm = rewriter.nm();
  return nm.mk_value(false);
}

// (define-rule contradictory-zero-test ((x0 ?BitVec) (p0 Bool) (p1 Bool))
//   (and
//     (not (= (@bv 0 (@bvsize x0)) x0))
//     (and (and (= (@bv 0 (@bvsize x0)) x0) p0) p1))
//   false)
bool
match_contradictory_zero_test(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::NOT || n3.kind() != Kind::AND)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::EQUAL)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      if (!is_zero(n6))
      {
        continue;
      }
      if (!n4[1 - i5].type().is_bv())
      {
        continue;
      }
      const Node& x0 = n4[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[i7];
        if (n8.kind() != Kind::AND)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10.kind() != Kind::EQUAL)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[i11];
            const Node& n13 = n10[1 - i11];
            if (!is_zero(n12))
            {
              continue;
            }
            if (n13 != x0)
            {
              continue;
            }
            const Node& p0 = n8[1 - i9];
            const Node& p1 = n3[1 - i7];
            vars[0]        = x0;
            vars[1]        = p0;
            vars[2]        = p1;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_contradictory_zero_test(Rewriter& rewriter, const Node* vars)
{
  (void) rewriter;
  (void) vars;
  NodeManager& nm = rewriter.nm();
  return nm.mk_value(false);
}

// (define-rule double-bitwise-negation-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot (bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_double_bitwise_negation_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_NOT || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_NOT || !is_one(n7))
      {
        continue;
      }
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_double_bitwise_negation_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  return t1;
}

// (define-rule double-negated-sum-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))
//   (bvadd x0 x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_double_negated_sum_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& n7 = n5[0];
      if (n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_double_negated_sum_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule factor-bitwise-and ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvand (bvand (bvnot (bvand x0 x1)) x2) x0)
//   (bvand x0 x2 (bvnot x1)))
bool
match_factor_bitwise_and(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n5 = n4[0];
      if (n5.kind() != Kind::BV_AND)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n5[i6];
        const Node& x1 = n5[1 - i6];
        const Node& x2 = n2[1 - i3];
        if (node[1 - i1] != x0)
        {
          continue;
        }
        vars[0] = x0;
        vars[1] = x1;
        vars[2] = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_factor_bitwise_and(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t2, t1});
  return t3;
}

// (define-rule factor-common-bitvector-multiplier-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvmul x0 x2))
//   (bvmul x0 (bvadd x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_bitvector_multiplier_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_MUL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        if (n6 != x0)
        {
          continue;
        }
        const Node& x2 = n3[1 - i5];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_factor_common_bitvector_multiplier_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  return t2;
}

// (define-rule factor-common-bit-vector-multiplicand
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd x2 (bvmul (bvmul x0 x3) x4)))
//   (bvadd (bvmul x0 (bvadd x1 (bvmul x3 x4))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_bit_vector_multiplicand(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[1 - i5];
        if (n6.kind() != Kind::BV_MUL)
        {
          continue;
        }
        const Node& x2 = n3[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n6[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_bit_vector_multiplicand(Rewriter& rewriter,
                                            const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[3], vars[4]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule factor-common-bv-mul
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul (bvmul x0 x1) x2) (bvadd (bvmul x2 x3) x4))
//   (bvadd (bvmul x2 (bvadd (bvmul x0 x1) x3)) x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_bv_mul(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_MUL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n5[i6];
        const Node& x1 = n5[1 - i6];
        const Node& x2 = n2[1 - i4];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x2)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n3[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_bv_mul(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[2], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[4]});
  return t4;
}

// (define-rule factor-common-bv-multiply
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul (bvmul x0 x1) x2) (bvadd (bvmul x0 x3) x4))
//   (bvadd (bvmul x0 (bvadd (bvmul x1 x2) x3)) x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_bv_multiply(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_MUL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n5[i6];
        const Node& x1 = n5[1 - i6];
        const Node& x2 = n2[1 - i4];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n3[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_bv_multiply(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[4]});
  return t4;
}

// (define-rule factor-common-multiplicand
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) x3))
//   (bvadd (bvmul x0 (bvadd x1 x2)) x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        if (n6.kind() != Kind::BV_MUL)
        {
          continue;
        }
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (n8 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i7];
          const Node& x3 = n3[1 - i5];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule factor-common-multiplicand-10
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 (bvadd x1 x2)) (bvadd (bvmul x0 x3) x4))
//   (bvadd (bvmul x0 (bvadd x1 x2 x3)) x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_10(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n5[i6];
        const Node& x2 = n5[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n3[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_10(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[4]});
  return t4;
}

// (define-rule factor-common-multiplicand-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvadd x3 x4)))
//   (bvadd (bvmul x0 (bvadd x1 x2)) (bvadd x3 x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (n6.kind() != Kind::BV_MUL || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& x3 = n7[i10];
            const Node& x4 = n7[1 - i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[3], vars[4]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplicand-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd x2 (bvadd (bvmul x0 x3) x4)))
//   (bvadd (bvmul x0 (bvadd x1 x3)) (bvadd x2 x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[1 - i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x2 = n3[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n6[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[4]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplicand-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (= x0 (bvadd (bvmul x1 x2) (bvadd (bvmul x1 x3) x4)))
//   (= x0 (bvadd (bvmul x1 (bvadd x2 x3)) x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_MUL || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n4[i6];
        const Node& x2 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x1)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n5[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_4(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[4]});
  Node t4 = rewriter.mk_node(Kind::EQUAL, {vars[0], t3});
  return t4;
}

// (define-rule factor-common-multiplicand-5
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvmul x0 x1) (bvmul x0 x2)) (@bv 1 (@bvsize x0)))
//   (bvadd (bvmul x0 (bvadd x1 x2)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_5(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_MUL || n6.kind() != Kind::BV_MUL)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n5[i7];
        const Node& x1 = n5[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_5(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplicand-6
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (= x0 (bvadd (bvadd (bvmul x1 x2) (bvmul x1 x3)) (@bv 1 (@bvsize x0))))
//   (= x0 (bvadd (bvmul x1 (bvadd x2 x3)) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_6(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_MUL || n8.kind() != Kind::BV_MUL)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x1 = n7[i9];
          const Node& x2 = n7[1 - i9];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n8[i10];
            if (n11 != x1)
            {
              continue;
            }
            const Node& x3 = n8[1 - i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_6(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t2         = rewriter.mk_node(Kind::BV_MUL, {vars[1], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::EQUAL, {vars[0], t4});
  return t5;
}

// (define-rule factor-common-multiplicand-7
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvadd (bvmul x0 x1) x2) (bvadd (bvmul x0 x3) x4))
//   (bvadd (bvmul x0 (bvadd x1 x3)) (bvadd x2 x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_7(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_MUL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n5[i6];
        const Node& x1 = n5[1 - i6];
        const Node& x2 = n2[1 - i4];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n3[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_7(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[4]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplicand-8
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvmul x3 x4)))
//   (bvadd (bvmul x0 (bvadd x1 x2)) (bvmul x3 x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_8(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (n6.kind() != Kind::BV_MUL || n7.kind() != Kind::BV_MUL)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& x3 = n7[i10];
            const Node& x4 = n7[1 - i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_8(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[3], vars[4]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplicand-9
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvmul (bvmul x0 x2) x3))
//   (bvmul x0 (bvadd x1 (bvmul x2 x3))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplicand_9(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_MUL)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        if (n6.kind() != Kind::BV_MUL)
        {
          continue;
        }
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          if (n8 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i7];
          const Node& x3 = n3[1 - i5];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplicand_9(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[2], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  return t3;
}

// (define-rule factor-common-multiplier
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd x0 (bvadd (bvmul x1 x2) (bvadd (bvmul x1 x3) x4)))
//   (bvadd x0 (bvadd (bvmul x1 (bvadd x2 x3)) x4)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplier(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_MUL || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n4[i6];
        const Node& x2 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x1)
            {
              continue;
            }
            const Node& x3 = n8[1 - i9];
            const Node& x4 = n5[1 - i7];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplier(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[2], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[4]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule factor-common-multiplier-3
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd x2 (bvmul (bvmul x3 x4) x0)))
//   (bvadd x2 (bvmul x0 (bvadd x1 (bvmul x3 x4)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplier_3(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[1 - i5];
        if (n6.kind() != Kind::BV_MUL)
        {
          continue;
        }
        const Node& x2 = n3[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          const Node& n9 = n6[1 - i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& x3 = n8[i10];
            const Node& x4 = n8[1 - i10];
            if (n9 != x0)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = x2;
            vars[3] = x3;
            vars[4] = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplier_3(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[3], vars[4]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t3});
  return t4;
}

// (define-rule factor-common-multiplier-4
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvadd x0 x3)))
//   (bvadd (bvmul x0 (bvadd x1 x2)) (bvadd x0 x3)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplier_4(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_MUL || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        const Node& n7 = n3[1 - i5];
        if (n6.kind() != Kind::BV_MUL || n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n7[i10];
            if (n11 != x0)
            {
              continue;
            }
            const Node& x3 = n7[1 - i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplier_4(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[3]});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule factor-common-multiplier-5
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvadd (bvadd (bvmul x0 x1) (bvmul (bvmul x0 x2) x3)) x4)
//   (bvadd (bvmul x0 (bvadd x1 (bvmul x2 x3))) x4))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_factor_common_multiplier_5(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_MUL || n5.kind() != Kind::BV_MUL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x0 = n4[i6];
        const Node& x1 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[i7];
          if (n8.kind() != Kind::BV_MUL)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (n10 != x0)
            {
              continue;
            }
            const Node& x2 = n8[1 - i9];
            const Node& x3 = n5[1 - i7];
            const Node& x4 = node[1 - i1];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            vars[4]        = x4;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_common_multiplier_5(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_MUL, {vars[2], vars[3]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3 = rewriter.mk_node(Kind::BV_MUL, {vars[0], t2});
  Node t4 = rewriter.mk_node(Kind::BV_ADD, {t3, vars[4]});
  return t4;
}

// (define-rule factor-shared-bitwise-and
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvand (bvand x0 x1) (bvand (bvnot (bvand (bvand x0 x1) x2)) x3))
//   (bvand x0 x1 (bvnot x2) x3))
bool
match_factor_shared_bitwise_and(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND || n3.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& x0 = n2[i4];
      const Node& x1 = n2[1 - i4];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n3[i5];
        if (n6.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n7 = n6[0];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (n9.kind() != Kind::BV_AND)
          {
            continue;
          }
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n9[i10];
            const Node& n12 = n9[1 - i10];
            if (n11 != x0)
            {
              continue;
            }
            if (n12 != x1)
            {
              continue;
            }
            const Node& x2 = n7[1 - i8];
            const Node& x3 = n3[1 - i5];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_shared_bitwise_and(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t2, t1});
  Node t4 = rewriter.mk_node(Kind::BV_AND, {t3, vars[3]});
  return t4;
}

// (define-rule factor-shared-xor-mask
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))
//   (bvxor (bvand x0 (bvxor (bvand x1 x2) x3)) (bvxor (bvand x1 x2) x4))
//   (bvxor (bvand (bvnot x0) (bvand x1 x2)) (bvxor (bvand x0 x3) x4)))
bool
match_factor_shared_xor_mask(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND || n3.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x1 = n7[i8];
          const Node& x2 = n7[1 - i8];
          const Node& x3 = n5[1 - i6];
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n3[i9];
            if (n10.kind() != Kind::BV_AND)
            {
              continue;
            }
            for (size_t i11 = 0; i11 < 2; ++i11)
            {
              const Node& n12 = n10[i11];
              const Node& n13 = n10[1 - i11];
              if (n12 != x1)
              {
                continue;
              }
              if (n13 != x2)
              {
                continue;
              }
              const Node& x4 = n3[1 - i9];
              vars[0]        = x0;
              vars[1]        = x1;
              vars[2]        = x2;
              vars[3]        = x3;
              vars[4]        = x4;
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

Node
build_factor_shared_xor_mask(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[3]});
  Node t5 = rewriter.mk_node(Kind::BV_XOR, {t4, vars[4]});
  Node t6 = rewriter.mk_node(Kind::BV_XOR, {t3, t5});
  return t6;
}

// (define-rule flatten-bitvector-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))
//   (bvadd x0 x1 x2 (bvnot (@bv 0 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_flatten_bitvector_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[i11];
            if (!is_ones(n12))
            {
              continue;
            }
            const Node& x1 = n10[1 - i11];
            const Node& x2 = n8[1 - i9];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_flatten_bitvector_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_ones(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule flatten-bvadd-and-cancel-ones
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd
//       (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))
//       x2))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_flatten_bvadd_and_cancel_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || !is_one(n8))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x0 = n7[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x1 = n10[i11];
            const Node& x2 = n3[1 - i4];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_flatten_bvadd_and_cancel_ones(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule flatten-bvadd-constants ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_flatten_bvadd_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n10[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_flatten_bvadd_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule fold-additive-constants-before-not
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//       (bvadd x2 (@bv 1 (@bvsize x0)))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_additive_constants_before_not(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n4[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n4[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_additive_constants_before_not(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule fold-additive-offsets
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)
//     (bvadd x3 (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_additive_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x0 = n8[i9];
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n2[1 - i4];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n3[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n3[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_fold_additive_offsets(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule fold-arithmetic-offsets-before-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//       (bvadd x2 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_arithmetic_offsets_before_arithmetic_shift(const Node& node,
                                                      Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n4[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n4[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_arithmetic_offsets_before_arithmetic_shift(Rewriter& rewriter,
                                                      const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule fold-bitvector-offsets ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd x0 (@bv 1 (@bvsize x0)))
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_bitvector_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (!is_one(n5))
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (n10.kind() != Kind::BV_ADD)
          {
            continue;
          }
          const Node& x1 = n8[i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n10[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n10[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_fold_bitvector_offsets(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule fold-bvadd-bvnot-constants ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvadd x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd x0 (bvnot x1) (@bv 3 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_bvadd_bvnot_constants(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x0 = n5[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[i9];
          const Node& n11 = n6[1 - i9];
          if (n10.kind() != Kind::BV_NOT || !is_one(n11))
          {
            continue;
          }
          const Node& x1 = n10[0];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_bvadd_bvnot_constants(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t2});
  return t4;
}

// (define-rule fold-cancelled-addends-before-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvashr
//       (bvadd
//         (@bv 1 (@bvsize x0))
//         (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//       (@bv 1 (@bvsize x0)))
//     x2)
//   (bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_cancelled_addends_before_arithmetic_shift(const Node& node,
                                                     Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x0 = n8[1 - i9];
          const Node& x1 = n6[1 - i7];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_cancelled_addends_before_arithmetic_shift(Rewriter& rewriter,
                                                     const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule fold-complemented-addends
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 x1 (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_complemented_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n3[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x2 = n9[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_complemented_addends(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule fold-complemented-addition
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvnot x0) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_complemented_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_NOT || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n3[0];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x1 = n4[i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x2 = n6[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_fold_complemented_addition(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule fold-minus-one-and-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2) (@bv 1 (@bvsize x0))))
//   (bvadd x0 x2 (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_minus_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_ADD || !is_one(n8))
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (n10.kind() != Kind::BV_ASHR)
          {
            continue;
          }
          if (!is_one(n10[1]))
          {
            continue;
          }
          const Node& x1 = n10[0];
          const Node& x2 = n7[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_minus_one_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t2});
  return t4;
}

// (define-rule fold-minus-one-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//     (bvadd x3 (@bv 1 (@bvsize x0))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_minus_one_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n7[i8];
          if (!is_ones(n9))
          {
            continue;
          }
          const Node& x1 = n7[1 - i8];
          const Node& x2 = n5[1 - i6];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n3[1 - i10];
            if (!is_one(n11))
            {
              continue;
            }
            const Node& x3 = n3[i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_fold_minus_one_plus_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule fold-minus-one-plus-one-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3))))
//   (bvadd x0 x1 x2 x3))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_minus_one_plus_one_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& x2 = n8[i11];
            const Node& x3 = n8[1 - i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_fold_minus_one_plus_one_2(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  return t3;
}

// (define-rule fold-negated-increment ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 (bvxor x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_negated_increment(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n6[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n7[i10];
          const Node& x2 = n7[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_negated_increment(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule fold-negative-one-addition ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd
//       (bvadd
//         (@bv 1 (@bvsize x0))
//         (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//       x1))
//   (bvadd x1 (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_negative_one_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x0 = n9[i10];
          const Node& x1 = n3[1 - i4];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_negative_one_addition(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t3});
  return t4;
}

// (define-rule fold-negative-one-and-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))
//     (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_fold_negative_one_and_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ASHR || !is_one(n6))
      {
        continue;
      }
      if (!is_one(n5[1]))
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n3[i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n8[1 - i9];
          const Node& x2 = n3[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_fold_negative_one_and_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, vars[2]});
  return t4;
}

// (define-rule grouped-add-complement-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 x3))
//   (bvnot
//     (bvadd
//       (bvnot (bvadd x0 x1))
//       (bvnot x2)
//       (bvnot x3)
//       (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_grouped_add_complement_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& x2 = n3[i8];
          const Node& x3 = n3[1 - i8];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_grouped_add_complement_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t5         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t7         = rewriter.mk_node(Kind::BV_ADD, {t6, t4});
  Node t8         = rewriter.mk_node(Kind::BV_ADD, {t7, t5});
  Node t9         = rewriter.mk_node(Kind::BV_NOT, {t8});
  return t9;
}

// (define-rule invert-decrement-equality
//     ((p0 Bool) (p1 Bool) (p2 Bool) (x0 ?BitVec) (x1 ?BitVec))
//   (and p0 (and (and p1 p2) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))
//   (and p0 (and p1 (and p2 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_invert_decrement_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::AND)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::AND)
    {
      continue;
    }
    const Node& p0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::AND || n5.kind() != Kind::EQUAL)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& p1 = n4[i6];
        const Node& p2 = n4[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n5[i7];
          if (n8.kind() != Kind::BV_ADD)
          {
            continue;
          }
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            if (!is_ones(n10))
            {
              continue;
            }
            const Node& x0 = n8[1 - i9];
            // The result is not in normal form for bit-width 1.
            if (x0.type().bv_size() < 2)
            {
              return false;
            }
            if (!n5[1 - i7].type().is_bv())
            {
              continue;
            }
            const Node& x1 = n5[1 - i7];
            vars[0]        = p0;
            vars[1]        = p1;
            vars[2]        = p2;
            vars[3]        = x0;
            vars[4]        = x1;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_invert_decrement_equality(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[3].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[4], t1});
  Node t3         = rewriter.mk_node(Kind::EQUAL, {t2, vars[3]});
  Node t4         = rewriter.mk_node(Kind::AND, {vars[2], t3});
  Node t5         = rewriter.mk_node(Kind::AND, {vars[1], t4});
  Node t6         = rewriter.mk_node(Kind::AND, {vars[0], t5});
  return t6;
}

// (define-rule merge-negated-addends ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))) (bvnot x2))
//   (bvadd x1 (bvnot (bvadd x0 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_merge_negated_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        const Node& x2 = n3[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_merge_negated_addends(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  return t3;
}

// (define-rule move-complemented-addend-across-equality
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (= x0 (bvadd (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))) x3))
//   (= (bvadd x0 x2) (bvadd x1 x3)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_move_complemented_addend_across_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[1 - i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i5];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[i7];
          const Node& n9 = n6[1 - i7];
          if (n8.kind() != Kind::BV_NOT || !is_one(n9))
          {
            continue;
          }
          const Node& x2 = n8[0];
          const Node& x3 = n2[1 - i3];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_move_complemented_addend_across_equality(Rewriter& rewriter,
                                               const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[3]});
  Node t3 = rewriter.mk_node(Kind::EQUAL, {t1, t2});
  return t3;
}

// (define-rule move-negated-addend ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= x0
//     (bvadd
//       (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0))))
//   (= (bvadd x0 x2) (bvadd x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_move_negated_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!node[i1].type().is_bv())
    {
      continue;
    }
    const Node& x0 = node[i1];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || !is_one(n5))
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[1 - i6];
        if (n7.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n4[i6];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n7[i8];
          const Node& n10 = n7[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x2 = n9[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_move_negated_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t1, t3});
  return t4;
}

// (define-rule negated-difference-arithmetic-shift ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvashr
//       (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0))))
//   (bvashr (bvadd (bvnot x0) x1) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_negated_difference_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD || !is_one(n1[1]))
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[1 - i3];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[i3];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_NOT || !is_one(n7))
      {
        continue;
      }
      const Node& x1 = n6[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_negated_difference_arithmetic_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[1]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule negated-sum-and ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvnot (bvand x0 x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd (bvand x0 x1) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_negated_sum_and(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x0 = n4[i5];
      const Node& x1 = n4[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_negated_sum_and(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule negated-sum-complement ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))
//   (bvnot (bvadd x0 x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_negated_sum_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[0];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT || !is_one(n6))
      {
        continue;
      }
      const Node& x1 = n5[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_negated_sum_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  return t2;
}

// (define-rule negated-sum-reassociation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) (bvnot x2))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_negated_sum_reassociation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = n3[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_negated_sum_reassociation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule normalize-addition-and-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (not
//     (= x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))
//   (not (= x0 (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_normalize_addition_and_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::NOT)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    if (!n1[i2].type().is_bv())
    {
      continue;
    }
    const Node& x0 = n1[i2];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_normalize_addition_and_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::EQUAL, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::NOT, {t2});
  return t3;
}

// (define-rule normalize-add-negated-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvadd (bvadd x0 (bvadd (bvadd x1 (bvnot x0)) x2)) x3)
//   (bvnot
//     (bvadd (bvadd (bvnot x1) (bvnot x2) (bvnot x3)) (@bv 3 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_normalize_add_negated_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        if (n6.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n6[1 - i7];
          if (n8.kind() != Kind::BV_NOT)
          {
            continue;
          }
          const Node& x1 = n6[i7];
          if (n8[0] != x0)
          {
            continue;
          }
          const Node& x2 = n4[1 - i5];
          const Node& x3 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_normalize_add_negated_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, t3});
  Node t6         = nm.mk_value(BitVector::from_si(size, 3, true));
  Node t7         = rewriter.mk_node(Kind::BV_ADD, {t5, t6});
  Node t8         = rewriter.mk_node(Kind::BV_NOT, {t7});
  return t8;
}

// (define-rule normalize-arithmetic-shift-expression
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvashr
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (@bv 1 (@bvsize x0)))
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd
//     (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     x1
//     (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_normalize_arithmetic_shift_expression(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n7[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n3[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n3[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_normalize_arithmetic_shift_expression(Rewriter& rewriter,
                                            const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, vars[1]});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t5, t1});
  return t6;
}

// (define-rule not-ashr-add-one ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvashr (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))
//   (bvashr (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_not_ashr_add_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD || !is_one(n1[1]))
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[1 - i3];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n2[i3];
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (!is_one(n6))
      {
        continue;
      }
      const Node& x1 = n4[i5];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_not_ashr_add_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = nm.mk_value(BitVector::mk_one(size));
  Node t5         = rewriter.mk_node(Kind::BV_ASHR, {t3, t4});
  return t5;
}

// (define-rule not-of-three-way-sum ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2))
//     (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_not_of_three_way_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (!is_one(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x0 = n9[i10];
          const Node& x1 = n9[1 - i10];
          const Node& x2 = n4[1 - i5];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_not_of_three_way_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule not-sum-via-complement ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 (bvadd (bvnot x1) (bvnot x2))))
//   (bvadd x0 (bvnot (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_not_sum_via_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& x1 = n7[0];
        const Node& x2 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_not_sum_via_complement(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  return t3;
}

// (define-rule reassociate-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvadd x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))
//   (bvadd x2 (bvnot (bvadd x0 x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_reassociate_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x0 = n3[i5];
      const Node& x1 = n3[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_reassociate_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  return t3;
}

// (define-rule remove-negative-one-addend ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     (bvadd x1 (@bv 1 (@bvsize x0))))
//   (bvadd x1 (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_remove_negative_one_addend(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ADD || !is_one(n6[1]))
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x0 = n7[i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n3[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n3[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_remove_negative_one_addend(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t3});
  return t4;
}

// (define-rule remove-zero-plus-one ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd (bvashr x2 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//   (bvadd (bvadd x0 x1) (bvashr x2 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_remove_zero_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (n9.kind() != Kind::BV_ASHR || !is_one(n10))
          {
            continue;
          }
          if (!is_one(n9[1]))
          {
            continue;
          }
          const Node& x2 = n9[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_remove_zero_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {vars[2], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule signed-half-plus-low-bit ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd x0
//       (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))
//     x1)
//   (bvadd x1
//     (bvadd
//       (bvashr x0 (@bv 1 (@bvsize x0)))
//       (bvand x0 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_signed_half_plus_low_bit(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n2[i3];
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        const Node& n7 = n4[1 - i5];
        if (!is_one(n6) || n7.kind() != Kind::BV_NOT)
        {
          continue;
        }
        const Node& n8 = n7[0];
        if (n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        if (n8[0] != x0)
        {
          continue;
        }
        const Node& x1 = node[1 - i1];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_signed_half_plus_low_bit(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_AND, {vars[0], t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t4});
  return t5;
}

// (define-rule signed-positive-increment-sum-2
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvslt
//     (@bv 0 (@bvsize x0))
//     (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd x2 x3)))
//   (and
//     (not (bvslt (bvadd x0 x1 x2 x3) (@bv 0 (@bvsize x0))))
//     (not
//       (=
//         (bvadd x0 x1 x2 x3)
//         (bvlshr (bvnot (@bv 0 (@bvsize x0))) (@bv 1 (@bvsize x0)))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_signed_positive_increment_sum_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_SLT)
  {
    return false;
  }
  const Node& n1 = node[1];
  if (!is_zero(node[0]) || n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_one(n6) || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x0 = n7[i8];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        const Node& x1 = n7[1 - i8];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x2 = n4[i9];
          const Node& x3 = n4[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_signed_positive_increment_sum_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  Node t4         = nm.mk_value(BitVector::mk_zero(size));
  Node t5         = rewriter.mk_node(Kind::BV_SLT, {t3, t4});
  Node t6         = rewriter.mk_node(Kind::NOT, {t5});
  Node t7         = nm.mk_value(BitVector::mk_max_signed(size));
  Node t8         = rewriter.mk_node(Kind::EQUAL, {t3, t7});
  Node t9         = rewriter.mk_node(Kind::NOT, {t8});
  Node t10        = rewriter.mk_node(Kind::AND, {t6, t9});
  return t10;
}

// (define-rule signed-positive-of-sum-plus-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvslt
//     (@bv 0 (@bvsize x0))
//     (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3)))))
//   (and
//     (not (bvslt (bvadd x0 x1 x2 x3) (@bv 0 (@bvsize x0))))
//     (not
//       (=
//         (bvadd x0 x1 x2 x3)
//         (bvnot
//           (bvshl
//             (@bv 1 (@bvsize x0))
//             (@bv (- (@bvsize x0) 1) (@bvsize x0))))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_signed_positive_of_sum_plus_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_SLT)
  {
    return false;
  }
  const Node& n1 = node[1];
  if (!is_zero(node[0]) || n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& x2 = n8[i9];
          const Node& x3 = n8[1 - i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_signed_positive_of_sum_plus_one(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[3]});
  Node t4         = nm.mk_value(BitVector::mk_zero(size));
  Node t5         = rewriter.mk_node(Kind::BV_SLT, {t3, t4});
  Node t6         = rewriter.mk_node(Kind::NOT, {t5});
  Node t7         = nm.mk_value(BitVector::mk_max_signed(size));
  Node t8         = rewriter.mk_node(Kind::EQUAL, {t3, t7});
  Node t9         = rewriter.mk_node(Kind::NOT, {t8});
  Node t10        = rewriter.mk_node(Kind::AND, {t6, t9});
  return t10;
}

// (define-rule simplify-additive-complements
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1))
//     (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))
//   (bvadd (bvadd x0 x1) (bvnot x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_additive_complements(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n6[i7];
        const Node& x1 = n6[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9  = n3[i8];
          const Node& n10 = n3[1 - i8];
          if (n9.kind() != Kind::BV_NOT || !is_one(n10))
          {
            continue;
          }
          const Node& x2 = n9[0];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_additive_complements(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  return t3;
}

// (define-rule simplify-add-before-arithmetic-shift ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd x1 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_add_before_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n4[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_add_before_arithmetic_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  return t3;
}

// (define-rule simplify-add-complement-cancellation
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvxor
//     (bvadd
//       (bvnot (@bv 0 (@bvsize x0)))
//       (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))
//     x2)
//   (bvxor (bvadd (bvnot x0) x1) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_add_complement_cancellation(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n7[0];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_add_complement_cancellation(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_XOR, {t2, vars[2]});
  return t3;
}

// (define-rule simplify-add-negated-one
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvxor x0
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))
//   (bvnot (bvxor x0 (bvadd x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_add_negated_one(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_XOR)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_add_negated_one(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule simplify-add-negated-zero-offsets
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (@bv 1 (@bvsize x0))
//     (bvadd x0
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x1 x2 (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_add_negated_zero_offsets(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_one(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_ADD || n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n7[i9];
          if (!is_ones(n10))
          {
            continue;
          }
          const Node& x1 = n7[1 - i9];
          for (size_t i11 = 0; i11 < 2; ++i11)
          {
            const Node& n12 = n8[1 - i11];
            if (!is_one(n12))
            {
              continue;
            }
            const Node& x2 = n8[i11];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_simplify_add_negated_zero_offsets(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule simplify-all-ones-addition ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//   (bvadd x0 (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_all_ones_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      if (!is_ones(n5))
      {
        continue;
      }
      const Node& x0 = n2[1 - i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n3[i6];
        const Node& n8 = n3[1 - i6];
        if (!is_one(n7) || n8.kind() != Kind::BV_ASHR)
        {
          continue;
        }
        const Node& n9 = n8[0];
        if (n9.kind() != Kind::BV_ADD || !is_one(n8[1]))
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n9[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_all_ones_addition(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule simplify-arithmetic-shifted-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvashr
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvadd x2 (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_arithmetic_shifted_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& x0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x1 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_arithmetic_shifted_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule simplify-arithmetic-shift-bias
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0
//     (bvashr
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))
//       (@bv 1 (@bvsize x0))))
//   (bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_arithmetic_shift_bias(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& x0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x1 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n8[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_arithmetic_shift_bias(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t3});
  return t4;
}

// (define-rule simplify-arithmetic-shift-expression ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_arithmetic_shift_expression(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (n8.kind() != Kind::BV_ASHR || !is_one(n9))
        {
          continue;
        }
        if (!is_one(n8[1]))
        {
          continue;
        }
        const Node& x1 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_arithmetic_shift_expression(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t3, t1});
  return t4;
}

// (define-rule simplify-arithmetic-shift-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0))))
//       (bvadd x1 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_arithmetic_shift_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n7[1]))
      {
        continue;
      }
      const Node& x0 = n7[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n4[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n4[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_arithmetic_shift_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t3, t1});
  return t4;
}

// (define-rule simplify-complemented-add
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvnot
//       (bvadd
//         (bvnot (@bv 0 (@bvsize x0)))
//         (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))))
//     x2)
//   (bvadd x2 (bvnot (bvadd x0 x1))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_complemented_add(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (n8.kind() != Kind::BV_ADD)
        {
          continue;
        }
        const Node& x0 = n6[i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n8[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x1 = n8[i9];
          const Node& x2 = node[1 - i1];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_complemented_add(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {vars[2], t2});
  return t3;
}

// (define-rule simplify-complemented-subtraction ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot x0) x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_complemented_subtraction(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_NOT || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_complemented_subtraction(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[1]});
  return t2;
}

// (define-rule simplify-complemented-sum
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvslt
//     (@bv 0 (@bvsize x0))
//     (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2))
//   (bvslt (@bv 0 (@bvsize x0)) (bvadd (bvadd (bvnot x0) (bvnot x1)) x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_complemented_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_SLT)
  {
    return false;
  }
  const Node& n1 = node[1];
  if (!is_zero(node[0]) || n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    if (n3.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& n4 = n3[0];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x0 = n4[i5];
      // The result is not in normal form for bit-width 1.
      if (x0.type().bv_size() < 2)
      {
        return false;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[1 - i7];
        if (!is_one(n8))
        {
          continue;
        }
        const Node& x1 = n6[i7];
        const Node& x2 = n1[1 - i2];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_complemented_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_zero(size));
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, vars[2]});
  Node t6         = rewriter.mk_node(Kind::BV_SLT, {t1, t5});
  return t6;
}

// (define-rule simplify-complemented-sum-shift ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvashr
//       (bvadd
//         (@bv 1 (@bvsize x0))
//         (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))
//       (@bv 1 (@bvsize x0))))
//   (bvashr
//     (bvadd (bvnot x0) (bvnot x1) (@bv 1 (@bvsize x0)))
//     (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_complemented_sum_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD || !is_one(n1[1]))
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[i3];
    const Node& n5 = n2[1 - i3];
    if (!is_one(n4) || n5.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i6 = 0; i6 < 2; ++i6)
    {
      const Node& n7 = n5[i6];
      if (n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n7[i8];
        if (!is_ones(n9))
        {
          continue;
        }
        const Node& x0 = n7[1 - i8];
        const Node& x1 = n5[1 - i6];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_complemented_sum_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, t3});
  Node t6         = rewriter.mk_node(Kind::BV_ASHR, {t5, t3});
  return t6;
}

// (define-rule simplify-negated-addends ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvnot (@bv 0 (@bvsize x0)))
//     (bvadd
//       (bvashr x0 (@bv 1 (@bvsize x0)))
//       (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))
//   (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_ones(n2) || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ASHR || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      if (!is_one(n5[1]))
      {
        continue;
      }
      const Node& x0 = n5[0];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (n8.kind() != Kind::BV_NOT || !is_one(n9))
        {
          continue;
        }
        const Node& x1 = n8[0];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_negated_addends(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ASHR, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  return t4;
}

// (define-rule simplify-negated-add-ones
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot
//     (bvadd x0
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x1)
//         (bvadd x2 (@bv 1 (@bvsize x0))))))
//   (bvnot (bvadd x0 x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_add_ones(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD || n6.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n5[i7];
        if (!is_ones(n8))
        {
          continue;
        }
        const Node& x1 = n5[1 - i7];
        for (size_t i9 = 0; i9 < 2; ++i9)
        {
          const Node& n10 = n6[1 - i9];
          if (!is_one(n10))
          {
            continue;
          }
          const Node& x2 = n6[i9];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_negated_add_ones(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule simplify-negated-arithmetic-shift ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd
//     (bvashr
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (@bv 1 (@bvsize x0)))
//     x1)
//   (bvadd
//     (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     x1))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_ones(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n6[0];
      const Node& x1 = node[1 - i1];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_simplify_negated_arithmetic_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {t4, vars[1]});
  return t5;
}

// (define-rule simplify-negated-arithmetic-shift-2 ((x0 ?BitVec))
//   (bvadd
//     (bvnot
//       (bvashr
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//         (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvadd
//     (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))
//     (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_arithmetic_shift_2(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT || !is_one(n3))
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ASHR)
    {
      continue;
    }
    const Node& n5 = n4[0];
    if (n5.kind() != Kind::BV_ADD || !is_one(n4[1]))
    {
      continue;
    }
    for (size_t i6 = 0; i6 < 2; ++i6)
    {
      const Node& n7 = n5[i6];
      const Node& n8 = n5[1 - i6];
      if (!is_ones(n7) || n8.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n8[0];
      vars[0]        = x0;
      return true;
    }
  }
  return false;
}

Node
build_simplify_negated_arithmetic_shift_2(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t3, t1});
  return t4;
}

// (define-rule simplify-negated-shifted-sum ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvashr
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//         (bvadd x1 (@bv 1 (@bvsize x0))))
//       (@bv 1 (@bvsize x0))))
//   (bvashr (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_shifted_sum(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  const Node& n2 = n1[0];
  if (n2.kind() != Kind::BV_ADD || !is_one(n1[1]))
  {
    return false;
  }
  for (size_t i3 = 0; i3 < 2; ++i3)
  {
    const Node& n4 = n2[i3];
    const Node& n5 = n2[1 - i3];
    if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i6 = 0; i6 < 2; ++i6)
    {
      const Node& n7 = n4[i6];
      if (!is_ones(n7))
      {
        continue;
      }
      const Node& x0 = n4[1 - i6];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n5[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n5[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_negated_shifted_sum(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule simplify-negated-zero-addends ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (bvadd x1 (@bv 1 (@bvsize x0))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x1 (bvnot x0)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negated_zero_addends(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      const Node& n7 = n3[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n7[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n4[1 - i8];
        if (!is_one(n9))
        {
          continue;
        }
        const Node& x1 = n4[i8];
        vars[0]        = x0;
        vars[1]        = x1;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_negated_zero_addends(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule simplify-negative-shifted-complement
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd
//     (bvashr
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0))
//       (@bv 1 (@bvsize x0)))
//     (bvadd x1 x2))
//   (bvadd
//     (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//     (bvadd x1 x2)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_negative_shifted_complement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ASHR || n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& n4 = n2[0];
    if (n4.kind() != Kind::BV_ADD || !is_one(n2[1]))
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (!is_ones(n6) || n7.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n7[0];
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& x1 = n3[i8];
        const Node& x2 = n3[1 - i8];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_negative_shifted_complement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_NOT, {t3});
  Node t5         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t6         = rewriter.mk_node(Kind::BV_ADD, {t4, t5});
  return t6;
}

// (define-rule simplify-nested-bvadd ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (@bv 1 (@bvsize x0))
//       (bvadd
//         (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//         (bvadd x1 (@bv 1 (@bvsize x0)))))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_nested_bvadd(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (!is_one(n3) || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n4[i5];
      const Node& n7 = n4[1 - i5];
      if (n6.kind() != Kind::BV_ADD || n7.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i8 = 0; i8 < 2; ++i8)
      {
        const Node& n9 = n6[i8];
        if (!is_ones(n9))
        {
          continue;
        }
        const Node& x0 = n6[1 - i8];
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n7[1 - i10];
          if (!is_one(n11))
          {
            continue;
          }
          const Node& x1 = n7[i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_nested_bvadd(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_one(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t3, t1});
  return t4;
}

// (define-rule simplify-nested-complement-add
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvnot (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))))
//   (bvadd x0 x2 (bvnot x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_nested_complement_add(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_NOT)
    {
      continue;
    }
    const Node& x0 = node[i1];
    const Node& n3 = n2[0];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[1 - i4];
      if (n5.kind() != Kind::BV_ADD)
      {
        continue;
      }
      const Node& x1 = n3[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n5[i6];
        const Node& n8 = n5[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_simplify_nested_complement_add(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, t1});
  return t3;
}

// (define-rule simplify-not-add-negated-shift ((x0 ?BitVec) (x1 ?BitVec))
//   (bvnot
//     (bvadd x0
//       (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))))
//   (bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0)))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_not_add_negated_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n1[i2];
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n3[i4];
      const Node& n6 = n3[1 - i4];
      if (!is_one(n5) || n6.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n7 = n6[0];
      if (n7.kind() != Kind::BV_ASHR)
      {
        continue;
      }
      if (!is_one(n7[1]))
      {
        continue;
      }
      const Node& x1 = n7[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_simplify_not_add_negated_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ASHR, {vars[1], t2});
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t1, t3});
  return t4;
}

// (define-rule simplify-offset-sum-arithmetic-shift
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_offset_sum_arithmetic_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (!is_one(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n9[i10];
          const Node& x2 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_offset_sum_arithmetic_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {t1, vars[2]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule simplify-shifted-double-add ((x0 ?BitVec) (x1 ?BitVec))
//   (bvashr
//     (bvadd
//       (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)
//       (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)))
//     (@bv 1 (@bvsize x0)))
//   (bvashr (bvadd x0 (bvadd x0 x1)) (@bv 1 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_simplify_shifted_double_add(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ASHR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD || !is_one(node[1]))
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_ADD || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& n6 = n3[i5];
      if (!is_ones(n6))
      {
        continue;
      }
      const Node& x0 = n3[1 - i5];
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n4[i7];
        const Node& n9 = n4[1 - i7];
        if (!is_one(n8) || n9.kind() != Kind::BV_ADD)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& n11 = n9[i10];
          if (n11 != x0)
          {
            continue;
          }
          const Node& x1 = n9[1 - i10];
          vars[0]        = x0;
          vars[1]        = x1;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_simplify_shifted_double_add(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_ADD, {vars[0], vars[1]});
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t1});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ASHR, {t2, t3});
  return t4;
}

// (define-rule subtraction-via-complemented-addition
//     ((x0 ?BitVec) (x1 ?BitVec))
//   (bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0)))
//   (bvnot (bvadd (bvnot x0) x1)))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_subtraction_via_complemented_addition(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD || !is_one(n3))
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      const Node& x1 = n5[0];
      vars[0]        = x0;
      vars[1]        = x1;
      return true;
    }
  }
  return false;
}

Node
build_subtraction_via_complemented_addition(Rewriter& rewriter,
                                            const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_ADD, {t1, vars[1]});
  Node t3 = rewriter.mk_node(Kind::BV_NOT, {t2});
  return t3;
}

// (define-rule xor-and-distribution-factor
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvxor (bvand (bvxor x0 x1) (bvxor x0 x2)) (bvxor x0 x3))
//   (bvxor (bvand x0 (bvxor x1 x2)) (bvand x1 x2) x3))
bool
match_xor_and_distribution_factor(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND || n3.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[i4];
      const Node& n6 = n2[1 - i4];
      if (n5.kind() != Kind::BV_XOR || n6.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x0 = n5[i7];
        const Node& x1 = n5[1 - i7];
        for (size_t i8 = 0; i8 < 2; ++i8)
        {
          const Node& n9 = n6[i8];
          if (n9 != x0)
          {
            continue;
          }
          const Node& x2 = n6[1 - i8];
          for (size_t i10 = 0; i10 < 2; ++i10)
          {
            const Node& n11 = n3[i10];
            if (n11 != x0)
            {
              continue;
            }
            const Node& x3 = n3[1 - i10];
            vars[0]        = x0;
            vars[1]        = x1;
            vars[2]        = x2;
            vars[3]        = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_xor_and_distribution_factor(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_AND, {vars[0], t1});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t4 = rewriter.mk_node(Kind::BV_XOR, {t2, t3});
  Node t5 = rewriter.mk_node(Kind::BV_XOR, {t4, vars[3]});
  return t5;
}

// (define-rule xor-complement-add-to-sub
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvxor x1 x2))))
//   (bvnot (bvadd (bvnot x0) (bvxor x1 x2))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_xor_complement_add_to_sub(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_ADD)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_one(n4) || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& x1 = n6[i7];
        const Node& x2 = n6[1 - i7];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_xor_complement_add_to_sub(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2 = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_NOT, {t3});
  return t4;
}

// (define-rule xor-mask-combine
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvxor (bvxor x0 (bvxor x1 x2)) (bvand x3 (bvxor x0 x1)))
//   (bvxor x2 (bvand (bvxor x0 x1) (bvnot x3))))
bool
match_xor_mask_combine(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_XOR || n3.kind() != Kind::BV_AND)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n5[i6];
        const Node& x2 = n5[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[1 - i7];
          if (n8.kind() != Kind::BV_XOR)
          {
            continue;
          }
          const Node& x3 = n3[i7];
          for (size_t i9 = 0; i9 < 2; ++i9)
          {
            const Node& n10 = n8[i9];
            const Node& n11 = n8[1 - i9];
            if (n10 != x0)
            {
              continue;
            }
            if (n11 != x1)
            {
              continue;
            }
            vars[0] = x0;
            vars[1] = x1;
            vars[2] = x2;
            vars[3] = x3;
            return true;
          }
        }
      }
    }
  }
  return false;
}

Node
build_xor_mask_combine(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_XOR, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[3]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t1, t2});
  Node t4 = rewriter.mk_node(Kind::BV_XOR, {vars[2], t3});
  return t4;
}

// (define-rule xor-mux-distribution
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))
//   (bvxor (bvand x0 (bvxor x1 x2)) (bvxor x1 x3))
//   (bvxor (bvxor (bvand x0 x2) (bvand (bvnot x0) x1)) x3))
bool
match_xor_mux_distribution(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND || n3.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i4 = 0; i4 < 2; ++i4)
    {
      const Node& n5 = n2[1 - i4];
      if (n5.kind() != Kind::BV_XOR)
      {
        continue;
      }
      const Node& x0 = n2[i4];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& x1 = n5[i6];
        const Node& x2 = n5[1 - i6];
        for (size_t i7 = 0; i7 < 2; ++i7)
        {
          const Node& n8 = n3[i7];
          if (n8 != x1)
          {
            continue;
          }
          const Node& x3 = n3[1 - i7];
          vars[0]        = x0;
          vars[1]        = x1;
          vars[2]        = x2;
          vars[3]        = x3;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_xor_mux_distribution(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_AND, {vars[0], vars[2]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t3 = rewriter.mk_node(Kind::BV_AND, {t2, vars[1]});
  Node t4 = rewriter.mk_node(Kind::BV_XOR, {t1, t3});
  Node t5 = rewriter.mk_node(Kind::BV_XOR, {t4, vars[3]});
  return t5;
}

// (define-rule xor-negated-decrement ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvxor x0
//     (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot (bvxor (bvand x1 x2) x0))))
//   (bvnot (bvxor x0 (bvadd (bvxor (bvand x1 x2) x0) (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_xor_negated_decrement(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (!is_ones(n4) || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      const Node& n6 = n5[0];
      if (n6.kind() != Kind::BV_XOR)
      {
        continue;
      }
      for (size_t i7 = 0; i7 < 2; ++i7)
      {
        const Node& n8 = n6[i7];
        const Node& n9 = n6[1 - i7];
        if (n8.kind() != Kind::BV_AND)
        {
          continue;
        }
        for (size_t i10 = 0; i10 < 2; ++i10)
        {
          const Node& x1 = n8[i10];
          const Node& x2 = n8[1 - i10];
          if (n9 != x0)
          {
            continue;
          }
          vars[0] = x0;
          vars[1] = x1;
          vars[2] = x2;
          return true;
        }
      }
    }
  }
  return false;
}

Node
build_xor_negated_decrement(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_AND, {vars[1], vars[2]});
  Node t2         = rewriter.mk_node(Kind::BV_XOR, {t1, vars[0]});
  Node t3         = nm.mk_value(BitVector::mk_one(size));
  Node t4         = rewriter.mk_node(Kind::BV_ADD, {t2, t3});
  Node t5         = rewriter.mk_node(Kind::BV_XOR, {vars[0], t4});
  Node t6         = rewriter.mk_node(Kind::BV_NOT, {t5});
  return t6;
}

// (define-rule xor-negation-add-rewrite
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (bvnot (bvadd (bvxor x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))
//   (bvadd (bvnot (bvxor x0 x1)) x2))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_xor_negation_add_rewrite(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_NOT)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  const Node& n1 = node[0];
  if (n1.kind() != Kind::BV_ADD)
  {
    return false;
  }
  for (size_t i2 = 0; i2 < 2; ++i2)
  {
    const Node& n3 = n1[i2];
    const Node& n4 = n1[1 - i2];
    if (n3.kind() != Kind::BV_XOR || n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x0 = n3[i5];
      const Node& x1 = n3[1 - i5];
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (n7.kind() != Kind::BV_NOT || !is_one(n8))
        {
          continue;
        }
        const Node& x2 = n7[0];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_xor_negation_add_rewrite(Rewriter& rewriter, const Node* vars)
{
  Node t1 = rewriter.mk_node(Kind::BV_XOR, {vars[0], vars[1]});
  Node t2 = rewriter.mk_node(Kind::BV_NOT, {t1});
  Node t3 = rewriter.mk_node(Kind::BV_ADD, {t2, vars[2]});
  return t3;
}

// (define-rule xor-not-decrement-pattern ((x0 ?BitVec))
//   (bvxor x0
//     (bvand (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvnot x0)))
//   (bvnot (bvand (bvnot x0) (bvadd x0 (@bv 1 (@bvsize x0))))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_xor_not_decrement_pattern(const Node& node, Node* vars)
{
  if (node.kind() != Kind::BV_XOR)
  {
    return false;
  }
  // The result is not in normal form for bit-width 1.
  if (node.type().bv_size() < 2)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[1 - i1];
    if (n2.kind() != Kind::BV_AND)
    {
      continue;
    }
    const Node& x0 = node[i1];
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      const Node& n5 = n2[1 - i3];
      if (n4.kind() != Kind::BV_ADD || n5.kind() != Kind::BV_NOT)
      {
        continue;
      }
      for (size_t i6 = 0; i6 < 2; ++i6)
      {
        const Node& n7 = n4[i6];
        const Node& n8 = n4[1 - i6];
        if (!is_ones(n7) || n8.kind() != Kind::BV_NOT)
        {
          continue;
        }
        if (n8[0] != x0)
        {
          continue;
        }
        if (n5[0] != x0)
        {
          continue;
        }
        vars[0] = x0;
        return true;
      }
    }
  }
  return false;
}

Node
build_xor_not_decrement_pattern(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_NOT, {vars[0]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {vars[0], t2});
  Node t4         = rewriter.mk_node(Kind::BV_AND, {t1, t3});
  Node t5         = rewriter.mk_node(Kind::BV_NOT, {t4});
  return t5;
}

// (define-rule xor-subtract-one-equality
//     ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= (bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1) x2)
//   (= (bvadd (bvxor x1 x2) (@bv 1 (@bvsize x0))) x0))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_xor_subtract_one_equality(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    if (n2.kind() != Kind::BV_XOR)
    {
      continue;
    }
    for (size_t i3 = 0; i3 < 2; ++i3)
    {
      const Node& n4 = n2[i3];
      if (n4.kind() != Kind::BV_ADD)
      {
        continue;
      }
      for (size_t i5 = 0; i5 < 2; ++i5)
      {
        const Node& n6 = n4[i5];
        if (!is_ones(n6))
        {
          continue;
        }
        const Node& x0 = n4[1 - i5];
        // The result is not in normal form for bit-width 1.
        if (x0.type().bv_size() < 2)
        {
          return false;
        }
        const Node& x1 = n2[1 - i3];
        if (!node[1 - i1].type().is_bv())
        {
          continue;
        }
        const Node& x2 = node[1 - i1];
        vars[0]        = x0;
        vars[1]        = x1;
        vars[2]        = x2;
        return true;
      }
    }
  }
  return false;
}

Node
build_xor_subtract_one_equality(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = rewriter.mk_node(Kind::BV_XOR, {vars[1], vars[2]});
  Node t2         = nm.mk_value(BitVector::mk_one(size));
  Node t3         = rewriter.mk_node(Kind::BV_ADD, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::EQUAL, {t3, vars[0]});
  return t4;
}

// (define-rule zero-after-left-shift ((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))
//   (= (@bv 0 (@bvsize x0)) (bvshl x0 (bvadd x1 x2)))
//   (=
//     (bvand x0 (bvlshr (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2)))
//     (@bv 0 (@bvsize x0))))
//
// Only applied to terms of bit-width >= 2 since the built-in rewrite rules
// rewrite the result of the rule (and its match pattern) at bit-width 1.
bool
match_zero_after_left_shift(const Node& node, Node* vars)
{
  if (node.kind() != Kind::EQUAL)
  {
    return false;
  }
  for (size_t i1 = 0; i1 < 2; ++i1)
  {
    const Node& n2 = node[i1];
    const Node& n3 = node[1 - i1];
    if (!is_zero(n2) || n3.kind() != Kind::BV_SHL)
    {
      continue;
    }
    const Node& n4 = n3[1];
    if (n4.kind() != Kind::BV_ADD)
    {
      continue;
    }
    const Node& x0 = n3[0];
    // The result is not in normal form for bit-width 1.
    if (x0.type().bv_size() < 2)
    {
      return false;
    }
    for (size_t i5 = 0; i5 < 2; ++i5)
    {
      const Node& x1 = n4[i5];
      const Node& x2 = n4[1 - i5];
      vars[0]        = x0;
      vars[1]        = x1;
      vars[2]        = x2;
      return true;
    }
  }
  return false;
}

Node
build_zero_after_left_shift(Rewriter& rewriter, const Node* vars)
{
  NodeManager& nm = rewriter.nm();
  uint64_t size   = vars[0].type().bv_size();
  Node t1         = nm.mk_value(BitVector::mk_ones(size));
  Node t2         = rewriter.mk_node(Kind::BV_ADD, {vars[1], vars[2]});
  Node t3         = rewriter.mk_node(Kind::BV_SHR, {t1, t2});
  Node t4         = rewriter.mk_node(Kind::BV_AND, {vars[0], t3});
  Node t5         = nm.mk_value(BitVector::mk_zero(size));
  Node t6         = rewriter.mk_node(Kind::EQUAL, {t4, t5});
  return t6;
}

/* --- Rule table ----------------------------------------------------------- */

using MatchFun = bool (*)(const Node&, Node*);
using BuildFun = Node (*)(Rewriter&, const Node*);

struct RuleInfo
{
  /** The RARE name of the rule. */
  const char* name;
  /** The kind of the root of the match pattern. */
  Kind root;
  /**
   * The kinds of the children of the root of the match pattern
   * (Kind::VALUE for values, Kind::NULL_NODE for variables).
   */
  Kind head0;
  Kind head1;
  /** True if the root of the match pattern is commutative. */
  bool commutative;
  MatchFun match;
  BuildFun build;
};

/** The rules, indexed by RareRuleKind. */
const RuleInfo s_rules[] = {
    {"additive-cancel-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_additive_cancel_ones,
     build_additive_cancel_ones},
    {"add-all-ones-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_add_all_ones_cancel,
     build_add_all_ones_cancel},
    {"add-complemented-negation",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_add_complemented_negation,
     build_add_complemented_negation},
    {"add-complement-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_add_complement_cancel,
     build_add_complement_cancel},
    {"add-negated-zero-offset",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_add_negated_zero_offset,
     build_add_negated_zero_offset},
    {"add-not-sum-cancel",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_NOT,
     true,
     match_add_not_sum_cancel,
     build_add_not_sum_cancel},
    {"add-not-sum-with-offset",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_add_not_sum_with_offset,
     build_add_not_sum_with_offset},
    {"add-one-via-complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_add_one_via_complemented_sum,
     build_add_one_via_complemented_sum},
    {"add-one-via-complemented-sum-2",
     Kind::BV_ADD,
     Kind::BV_XOR,
     Kind::BV_ADD,
     true,
     match_add_one_via_complemented_sum_2,
     build_add_one_via_complemented_sum_2},
    {"ashr-add-one-nontrivial",
     Kind::NOT,
     Kind::EQUAL,
     Kind::NULL_NODE,
     false,
     match_ashr_add_one_nontrivial,
     build_ashr_add_one_nontrivial},
    {"ashr-complement-add-rounding",
     Kind::BV_NOT,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     false,
     match_ashr_complement_add_rounding,
     build_ashr_complement_add_rounding},
    {"ashr-complement-negated-input",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_complement_negated_input,
     build_ashr_complement_negated_input},
    {"ashr-half-sum-fold",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_ashr_half_sum_fold,
     build_ashr_half_sum_fold},
    {"ashr-negated-increment",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_ashr_negated_increment,
     build_ashr_negated_increment},
    {"ashr-negated-sum",
     Kind::BV_ASHR,
     Kind::BV_NOT,
     Kind::VALUE,
     false,
     match_ashr_negated_sum,
     build_ashr_negated_sum},
    {"ashr-negated-sum-split",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_negated_sum_split,
     build_ashr_negated_sum_split},
    {"ashr-plus-low-bit",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_ashr_plus_low_bit,
     build_ashr_plus_low_bit},
    {"ashr-simplify-add-cancel",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_simplify_add_cancel,
     build_ashr_simplify_add_cancel},
    {"ashr-subtract-one-complement",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_subtract_one_complement,
     build_ashr_subtract_one_complement},
    {"ashr-sum-after-cancelled-offset",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_sum_after_cancelled_offset,
     build_ashr_sum_after_cancelled_offset},
    {"ashr-sum-cancel-ones",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_sum_cancel_ones,
     build_ashr_sum_cancel_ones},
    {"ashr-sum-minus-one-half",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_sum_minus_one_half,
     build_ashr_sum_minus_one_half},
    {"ashr-sum-offset-cancel",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_ashr_sum_offset_cancel,
     build_ashr_sum_offset_cancel},
    {"average-floor-signed-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_average_floor_signed_sum,
     build_average_floor_signed_sum},
    {"bvadd-allones-equality-reverse",
     Kind::AND,
     Kind::AND,
     Kind::EQUAL,
     true,
     match_bvadd_allones_equality_reverse,
     build_bvadd_allones_equality_reverse},
    {"bvadd-all-ones-as-minus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_all_ones_as_minus_one,
     build_bvadd_all_ones_as_minus_one},
    {"bvadd-all-ones-cancel-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_all_ones_cancel_one,
     build_bvadd_all_ones_cancel_one},
    {"bvadd-all-ones-equals-xor",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_all_ones_equals_xor,
     build_bvadd_all_ones_equals_xor},
    {"bvadd-cancel-allones",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_allones,
     build_bvadd_cancel_allones},
    {"bvadd-cancel-allones-and-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_allones_and_one,
     build_bvadd_cancel_allones_and_one},
    {"bvadd-cancel-allones-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_allones_plus_one,
     build_bvadd_cancel_allones_plus_one},
    {"bvadd-cancel-all-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_cancel_all_ones,
     build_bvadd_cancel_all_ones},
    {"bvadd-cancel-all-ones-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_2,
     build_bvadd_cancel_all_ones_2},
    {"bvadd-cancel-all-ones-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_cancel_all_ones_3,
     build_bvadd_cancel_all_ones_3},
    {"bvadd-cancel-all-ones-4",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_4,
     build_bvadd_cancel_all_ones_4},
    {"bvadd-cancel-all-ones-and-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_and_one,
     build_bvadd_cancel_all_ones_and_one},
    {"bvadd-cancel-all-ones-and-one-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_and_one_2,
     build_bvadd_cancel_all_ones_and_one_2},
    {"bvadd-cancel-all-ones-and-one-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_and_one_3,
     build_bvadd_cancel_all_ones_and_one_3},
    {"bvadd-cancel-all-ones-plus-one",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_plus_one,
     build_bvadd_cancel_all_ones_plus_one},
    {"bvadd-cancel-all-ones-with-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_all_ones_with_one,
     build_bvadd_cancel_all_ones_with_one},
    {"bvadd-cancel-complement",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_cancel_complement,
     build_bvadd_cancel_complement},
    {"bvadd-cancel-complemented-summand",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complemented_summand,
     build_bvadd_cancel_complemented_summand},
    {"bvadd-cancel-complement-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_2,
     build_bvadd_cancel_complement_2},
    {"bvadd-cancel-complement-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_3,
     build_bvadd_cancel_complement_3},
    {"bvadd-cancel-complement-4",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_4,
     build_bvadd_cancel_complement_4},
    {"bvadd-cancel-complement-offset",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_offset,
     build_bvadd_cancel_complement_offset},
    {"bvadd-cancel-complement-offset-2",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_offset_2,
     build_bvadd_cancel_complement_offset_2},
    {"bvadd-cancel-complement-offset-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_offset_3,
     build_bvadd_cancel_complement_offset_3},
    {"bvadd-cancel-complement-offset-4",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_complement_offset_4,
     build_bvadd_cancel_complement_offset_4},
    {"bvadd-cancel-minus-one-and-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_minus_one_and_one,
     build_bvadd_cancel_minus_one_and_one},
    {"bvadd-cancel-minus-one-and-one-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_minus_one_and_one_2,
     build_bvadd_cancel_minus_one_and_one_2},
    {"bvadd-cancel-minus-one-and-one-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_cancel_minus_one_and_one_3,
     build_bvadd_cancel_minus_one_and_one_3},
    {"bvadd-cancel-minus-one-offset",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_minus_one_offset,
     build_bvadd_cancel_minus_one_offset},
    {"bvadd-cancel-minus-one-plus-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_minus_one_plus_one,
     build_bvadd_cancel_minus_one_plus_one},
    {"bvadd-cancel-minus-one-plus-one-2",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_minus_one_plus_one_2,
     build_bvadd_cancel_minus_one_plus_one_2},
    {"bvadd-cancel-minus-one-plus-one-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_cancel_minus_one_plus_one_3,
     build_bvadd_cancel_minus_one_plus_one_3},
    {"bvadd-cancel-negated-zero",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_negated_zero,
     build_bvadd_cancel_negated_zero},
    {"bvadd-cancel-negative-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_negative_one,
     build_bvadd_cancel_negative_one},
    {"bvadd-cancel-negative-one-and-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_negative_one_and_one,
     build_bvadd_cancel_negative_one_and_one},
    {"bvadd-cancel-neg-one-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_cancel_neg_one_and_one,
     build_bvadd_cancel_neg_one_and_one},
    {"bvadd-cancel-neg-one-and-one-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_cancel_neg_one_and_one_2,
     build_bvadd_cancel_neg_one_and_one_2},
    {"bvadd-cancel-offset",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_offset,
     build_bvadd_cancel_offset},
    {"bvadd-cancel-offsets",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_offsets,
     build_bvadd_cancel_offsets},
    {"bvadd-cancel-ones",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvadd_cancel_ones,
     build_bvadd_cancel_ones},
    {"bvadd-cancel-one-minus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_one_minus_one,
     build_bvadd_cancel_one_minus_one},
    {"bvadd-cancel-one-minus-one-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_cancel_one_minus_one_2,
     build_bvadd_cancel_one_minus_one_2},
    {"bvadd-carry-constant-fold",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_carry_constant_fold,
     build_bvadd_carry_constant_fold},
    {"bvadd-collapse-all-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_collapse_all_ones,
     build_bvadd_collapse_all_ones},
    {"bvadd-combine-complemented-pair",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_combine_complemented_pair,
     build_bvadd_combine_complemented_pair},
    {"bvadd-complemented-negation",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_complemented_negation,
     build_bvadd_complemented_negation},
    {"bvadd-complement-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_complement_cancel,
     build_bvadd_complement_cancel},
    {"bvadd-complement-equality-xor",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_XOR,
     true,
     match_bvadd_complement_equality_xor,
     build_bvadd_complement_equality_xor},
    {"bvadd-complement-reassociate",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvadd_complement_reassociate,
     build_bvadd_complement_reassociate},
    {"bvadd-complement-sum",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_complement_sum,
     build_bvadd_complement_sum},
    {"bvadd-complement-sum-2",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_complement_sum_2,
     build_bvadd_complement_sum_2},
    {"bvadd-fold-minus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_fold_minus_one,
     build_bvadd_fold_minus_one},
    {"bvadd-fold-negated-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_fold_negated_one,
     build_bvadd_fold_negated_one},
    {"bvadd-inverse-rearrange",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_inverse_rearrange,
     build_bvadd_inverse_rearrange},
    {"bvadd-minus-one-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_minus_one_cancel,
     build_bvadd_minus_one_cancel},
    {"bvadd-minus-one-equality",
     Kind::EQUAL,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_minus_one_equality,
     build_bvadd_minus_one_equality},
    {"bvadd-minus-one-plus-one",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_minus_one_plus_one,
     build_bvadd_minus_one_plus_one},
    {"bvadd-minus-one-plus-one-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_minus_one_plus_one_2,
     build_bvadd_minus_one_plus_one_2},
    {"bvadd-minus-one-plus-one-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_minus_one_plus_one_3,
     build_bvadd_minus_one_plus_one_3},
    {"bvadd-minus-one-plus-one-4",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_minus_one_plus_one_4,
     build_bvadd_minus_one_plus_one_4},
    {"bvadd-minus-one-plus-one-5",
     Kind::BV_AND,
     Kind::BV_XOR,
     Kind::NULL_NODE,
     true,
     match_bvadd_minus_one_plus_one_5,
     build_bvadd_minus_one_plus_one_5},
    {"bvadd-minus-one-subtraction",
     Kind::EQUAL,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_minus_one_subtraction,
     build_bvadd_minus_one_subtraction},
    {"bvadd-negated-shift-cancellation",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ASHR,
     true,
     match_bvadd_negated_shift_cancellation,
     build_bvadd_negated_shift_cancellation},
    {"bvadd-negated-x1-and-arithmetic-shift",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_negated_x1_and_arithmetic_shift,
     build_bvadd_negated_x1_and_arithmetic_shift},
    {"bvadd-negated-zero-cancel",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_negated_zero_cancel,
     build_bvadd_negated_zero_cancel},
    {"bvadd-negated-zero-offset",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_negated_zero_offset,
     build_bvadd_negated_zero_offset},
    {"bvadd-neg-one-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_and_one,
     build_bvadd_neg_one_and_one},
    {"bvadd-neg-one-and-one-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_and_one_cancel,
     build_bvadd_neg_one_and_one_cancel},
    {"bvadd-neg-one-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_cancel,
     build_bvadd_neg_one_cancel},
    {"bvadd-neg-one-cancel-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_cancel_2,
     build_bvadd_neg_one_cancel_2},
    {"bvadd-neg-one-cancel-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_neg_one_cancel_3,
     build_bvadd_neg_one_cancel_3},
    {"bvadd-neg-one-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_plus_one,
     build_bvadd_neg_one_plus_one},
    {"bvadd-neg-one-plus-one-2",
     Kind::BV_XOR,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_plus_one_2,
     build_bvadd_neg_one_plus_one_2},
    {"bvadd-neg-one-plus-one-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_plus_one_cancel,
     build_bvadd_neg_one_plus_one_cancel},
    {"bvadd-neg-one-plus-one-cancellation",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_neg_one_plus_one_cancellation,
     build_bvadd_neg_one_plus_one_cancellation},
    {"bvadd-neg-one-plus-one-cancel-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_neg_one_plus_one_cancel_2,
     build_bvadd_neg_one_plus_one_cancel_2},
    {"bvadd-not-and-to-not-sum",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_bvadd_not_and_to_not_sum,
     build_bvadd_not_and_to_not_sum},
    {"bvadd-not-complement-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_not_complement_sum,
     build_bvadd_not_complement_sum},
    {"bvadd-not-subtract-simplification",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvadd_not_subtract_simplification,
     build_bvadd_not_subtract_simplification},
    {"bvadd-not-sub-constant",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_bvadd_not_sub_constant,
     build_bvadd_not_sub_constant},
    {"bvadd-not-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_NOT,
     true,
     match_bvadd_not_sum,
     build_bvadd_not_sum},
    {"bvadd-not-sum-plus-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_not_sum_plus_one,
     build_bvadd_not_sum_plus_one},
    {"bvadd-not-zero-collapse",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_not_zero_collapse,
     build_bvadd_not_zero_collapse},
    {"bvadd-ones-and-increment-cancel",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bvadd_ones_and_increment_cancel,
     build_bvadd_ones_and_increment_cancel},
    {"bvadd-one-as-complement",
     Kind::BV_ADD,
     Kind::BV_XOR,
     Kind::BV_ADD,
     true,
     match_bvadd_one_as_complement,
     build_bvadd_one_as_complement},
    {"bvadd-one-as-complement-negation",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_one_as_complement_negation,
     build_bvadd_one_as_complement_negation},
    {"bvadd-one-as-negated-complement",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ASHR,
     true,
     match_bvadd_one_as_negated_complement,
     build_bvadd_one_as_negated_complement},
    {"bvadd-one-complement-minus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_one_complement_minus_one,
     build_bvadd_one_complement_minus_one},
    {"bvadd-one-equals-bitwise-difference",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvadd_one_equals_bitwise_difference,
     build_bvadd_one_equals_bitwise_difference},
    {"bvadd-reassociate-complement",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_reassociate_complement,
     build_bvadd_reassociate_complement},
    {"bvadd-reassociate-complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvadd_reassociate_complemented_sum,
     build_bvadd_reassociate_complemented_sum},
    {"bvadd-sub-cancellation",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bvadd_sub_cancellation,
     build_bvadd_sub_cancellation},
    {"bvand-clear-bits",
     Kind::BV_AND,
     Kind::NULL_NODE,
     Kind::BV_AND,
     true,
     match_bvand_clear_bits,
     build_bvand_clear_bits},
    {"bvand-distribute-inverted-factor",
     Kind::BV_AND,
     Kind::NULL_NODE,
     Kind::BV_AND,
     true,
     match_bvand_distribute_inverted_factor,
     build_bvand_distribute_inverted_factor},
    {"bvand-equality-idempotence",
     Kind::AND,
     Kind::AND,
     Kind::EQUAL,
     true,
     match_bvand_equality_idempotence,
     build_bvand_equality_idempotence},
    {"bvand-mask-distribution",
     Kind::BV_AND,
     Kind::BV_AND,
     Kind::NULL_NODE,
     true,
     match_bvand_mask_distribution,
     build_bvand_mask_distribution},
    {"bvashr-cancel-additive-constants",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_bvashr_cancel_additive_constants,
     build_bvashr_cancel_additive_constants},
    {"bvashr-negated-difference",
     Kind::BV_ASHR,
     Kind::BV_NOT,
     Kind::VALUE,
     false,
     match_bvashr_negated_difference,
     build_bvashr_negated_difference},
    {"bvnot-add-cancel-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_NOT,
     true,
     match_bvnot_add_cancel_one,
     build_bvnot_add_cancel_one},
    {"bvnot-add-complement",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_complement,
     build_bvnot_add_complement},
    {"bvnot-add-complemented-and",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_complemented_and,
     build_bvnot_add_complemented_and},
    {"bvnot-add-identity",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_bvnot_add_identity,
     build_bvnot_add_identity},
    {"bvnot-add-inverse-cancel",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_inverse_cancel,
     build_bvnot_add_inverse_cancel},
    {"bvnot-add-mask-one",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_mask_one,
     build_bvnot_add_mask_one},
    {"bvnot-add-negated-subtrahend",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_negated_subtrahend,
     build_bvnot_add_negated_subtrahend},
    {"bvnot-add-negated-subtrahend-2",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_negated_subtrahend_2,
     build_bvnot_add_negated_subtrahend_2},
    {"bvnot-add-negated-sum",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_negated_sum,
     build_bvnot_add_negated_sum},
    {"bvnot-add-negation-collapse",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_negation_collapse,
     build_bvnot_add_negation_collapse},
    {"bvnot-add-normalize",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_normalize,
     build_bvnot_add_normalize},
    {"bvnot-add-one-and",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_one_and,
     build_bvnot_add_one_and},
    {"bvnot-add-one-collapse",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_bvnot_add_one_collapse,
     build_bvnot_add_one_collapse},
    {"bvnot-add-one-simplify",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_bvnot_add_one_simplify,
     build_bvnot_add_one_simplify},
    {"bvnot-add-plus-one",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_plus_one,
     build_bvnot_add_plus_one},
    {"bvnot-add-split",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_split,
     build_bvnot_add_split},
    {"bvnot-add-successor",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_bvnot_add_successor,
     build_bvnot_add_successor},
    {"bvnot-add-sum-complement",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_sum_complement,
     build_bvnot_add_sum_complement},
    {"bvnot-add-to-complement-sum",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_to_complement_sum,
     build_bvnot_add_to_complement_sum},
    {"bvnot-add-xor",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_xor,
     build_bvnot_add_xor},
    {"bvnot-add-zero-minus-one-3",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_add_zero_minus_one_3,
     build_bvnot_add_zero_minus_one_3},
    {"bvnot-allones-add-one",
     Kind::NOT,
     Kind::EQUAL,
     Kind::NULL_NODE,
     false,
     match_bvnot_allones_add_one,
     build_bvnot_allones_add_one},
    {"bvnot-incremented-sum",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::NULL_NODE,
     true,
     match_bvnot_incremented_sum,
     build_bvnot_incremented_sum},
    {"bvnot-minus-one-add",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_minus_one_add,
     build_bvnot_minus_one_add},
    {"bvnot-sum-collapse",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_sum_collapse,
     build_bvnot_sum_collapse},
    {"bvnot-sum-complements",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_sum_complements,
     build_bvnot_sum_complements},
    {"bvnot-sum-difference",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_sum_difference,
     build_bvnot_sum_difference},
    {"bvnot-sum-distribute",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bvnot_sum_distribute,
     build_bvnot_sum_distribute},
    {"bvnot-sum-grouped-negations",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_sum_grouped_negations,
     build_bvnot_sum_grouped_negations},
    {"bvnot-sum-with-increments",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_bvnot_sum_with_increments,
     build_bvnot_sum_with_increments},
    {"bvnot-sum-with-offset",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_bvnot_sum_with_offset,
     build_bvnot_sum_with_offset},
    {"bvnot-zero-add-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvnot_zero_add_cancel,
     build_bvnot_zero_add_cancel},
    {"bvnot-zero-add-equality",
     Kind::AND,
     Kind::AND,
     Kind::NOT,
     true,
     match_bvnot_zero_add_equality,
     build_bvnot_zero_add_equality},
    {"bvnot-zero-add-identity",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::NOT,
     true,
     match_bvnot_zero_add_identity,
     build_bvnot_zero_add_identity},
    {"bvnot-zero-add-identity-2",
     Kind::AND,
     Kind::EQUAL,
     Kind::AND,
     true,
     match_bvnot_zero_add_identity_2,
     build_bvnot_zero_add_identity_2},
    {"bvnot-zero-add-increment",
     Kind::AND,
     Kind::AND,
     Kind::EQUAL,
     true,
     match_bvnot_zero_add_increment,
     build_bvnot_zero_add_increment},
    {"bvnot-zero-add-inverse",
     Kind::NOT,
     Kind::EQUAL,
     Kind::NULL_NODE,
     false,
     match_bvnot_zero_add_inverse,
     build_bvnot_zero_add_inverse},
    {"bvnot-zero-add-invert",
     Kind::AND,
     Kind::AND,
     Kind::NOT,
     true,
     match_bvnot_zero_add_invert,
     build_bvnot_zero_add_invert},
    {"bvnot-zero-add-one-cancel",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvnot_zero_add_one_cancel,
     build_bvnot_zero_add_one_cancel},
    {"bvnot-zero-add-one-reassociate",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::NOT,
     true,
     match_bvnot_zero_add_one_reassociate,
     build_bvnot_zero_add_one_reassociate},
    {"bvnot-zero-add-reverse",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::NOT,
     true,
     match_bvnot_zero_add_reverse,
     build_bvnot_zero_add_reverse},
    {"bvnot-zero-plus-increment-inverse",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::EQUAL,
     true,
     match_bvnot_zero_plus_increment_inverse,
     build_bvnot_zero_plus_increment_inverse},
    {"bvnot-zero-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_bvnot_zero_plus_one,
     build_bvnot_zero_plus_one},
    {"bvnot-zero-plus-x-equality",
     Kind::NOT,
     Kind::AND,
     Kind::NULL_NODE,
     false,
     match_bvnot_zero_plus_x_equality,
     build_bvnot_zero_plus_x_equality},
    {"bvnot-zero-plus-x-equality-2",
     Kind::AND,
     Kind::AND,
     Kind::NULL_NODE,
     true,
     match_bvnot_zero_plus_x_equality_2,
     build_bvnot_zero_plus_x_equality_2},
    {"bvnot-zero-plus-x-equals-successor",
     Kind::AND,
     Kind::AND,
     Kind::NULL_NODE,
     true,
     match_bvnot_zero_plus_x_equals_successor,
     build_bvnot_zero_plus_x_equals_successor},
    {"bv-add-all-ones-cancel",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_bv_add_all_ones_cancel,
     build_bv_add_all_ones_cancel},
    {"bv-add-minus-one-offset",
     Kind::BV_XOR,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_bv_add_minus_one_offset,
     build_bv_add_minus_one_offset},
    {"bv-complement-plus-x-to-increment",
     Kind::AND,
     Kind::AND,
     Kind::EQUAL,
     true,
     match_bv_complement_plus_x_to_increment,
     build_bv_complement_plus_x_to_increment},
    {"bv-negated-sum-expression",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::BV_SLT,
     true,
     match_bv_negated_sum_expression,
     build_bv_negated_sum_expression},
    {"bv-sub-increment-equivalence",
     Kind::AND,
     Kind::NOT,
     Kind::NOT,
     true,
     match_bv_sub_increment_equivalence,
     build_bv_sub_increment_equivalence},
    {"bv-sub-via-negated-operands",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_bv_sub_via_negated_operands,
     build_bv_sub_via_negated_operands},
    {"cancelled-addend",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancelled_addend,
     build_cancelled_addend},
    {"cancel-additive-complement",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_additive_complement,
     build_cancel_additive_complement},
    {"cancel-additive-constants",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_cancel_additive_constants,
     build_cancel_additive_constants},
    {"cancel-additive-constants-before-arithmetic-shift",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_cancel_additive_constants_before_arithmetic_shift,
     build_cancel_additive_constants_before_arithmetic_shift},
    {"cancel-additive-inverses-signed-lt",
     Kind::BV_SLT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_cancel_additive_inverses_signed_lt,
     build_cancel_additive_inverses_signed_lt},
    {"cancel-additive-negation",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_additive_negation,
     build_cancel_additive_negation},
    {"cancel-additive-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_additive_ones,
     build_cancel_additive_ones},
    {"cancel-add-and-complement",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_add_and_complement,
     build_cancel_add_and_complement},
    {"cancel-add-complement",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_add_complement,
     build_cancel_add_complement},
    {"cancel-add-inverse",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_cancel_add_inverse,
     build_cancel_add_inverse},
    {"cancel-add-one-and-all-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_add_one_and_all_ones,
     build_cancel_add_one_and_all_ones},
    {"cancel-add-one-from-complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_cancel_add_one_from_complemented_sum,
     build_cancel_add_one_from_complemented_sum},
    {"cancel-all-ones-addend",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_addend,
     build_cancel_all_ones_addend},
    {"cancel-all-ones-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_cancel_all_ones_addends,
     build_cancel_all_ones_addends},
    {"cancel-all-ones-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_and_one,
     build_cancel_all_ones_and_one},
    {"cancel-all-ones-and-one-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_and_one_2,
     build_cancel_all_ones_and_one_2},
    {"cancel-all-ones-and-one-3",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_and_one_3,
     build_cancel_all_ones_and_one_3},
    {"cancel-all-ones-offset",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_offset,
     build_cancel_all_ones_offset},
    {"cancel-all-ones-offset-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_cancel_all_ones_offset_2,
     build_cancel_all_ones_offset_2},
    {"cancel-all-ones-plus-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_plus_one,
     build_cancel_all_ones_plus_one},
    {"cancel-all-ones-plus-one-2",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_all_ones_plus_one_2,
     build_cancel_all_ones_plus_one_2},
    {"cancel-bv-negated-zero-offset",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_cancel_bv_negated_zero_offset,
     build_cancel_bv_negated_zero_offset},
    {"cancel-complemented-addend",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_complemented_addend,
     build_cancel_complemented_addend},
    {"cancel-complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_complemented_sum,
     build_cancel_complemented_sum},
    {"cancel-complemented-zero-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_complemented_zero_and_one,
     build_cancel_complemented_zero_and_one},
    {"cancel-complement-addend",
     Kind::NOT,
     Kind::EQUAL,
     Kind::NULL_NODE,
     false,
     match_cancel_complement_addend,
     build_cancel_complement_addend},
    {"cancel-complement-increment",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_cancel_complement_increment,
     build_cancel_complement_increment},
    {"cancel-minus-one-and-one",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_cancel_minus_one_and_one,
     build_cancel_minus_one_and_one},
    {"cancel-minus-one-and-plus-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_minus_one_and_plus_one,
     build_cancel_minus_one_and_plus_one},
    {"cancel-minus-one-offset",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_minus_one_offset,
     build_cancel_minus_one_offset},
    {"cancel-minus-one-offset-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_minus_one_offset_2,
     build_cancel_minus_one_offset_2},
    {"cancel-minus-one-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_cancel_minus_one_plus_one,
     build_cancel_minus_one_plus_one},
    {"cancel-minus-one-plus-one-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_minus_one_plus_one_2,
     build_cancel_minus_one_plus_one_2},
    {"cancel-minus-one-plus-one-3",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_cancel_minus_one_plus_one_3,
     build_cancel_minus_one_plus_one_3},
    {"cancel-modular-offsets",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_modular_offsets,
     build_cancel_modular_offsets},
    {"cancel-negated-addend",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_cancel_negated_addend,
     build_cancel_negated_addend},
    {"cancel-negated-addend-2",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_negated_addend_2,
     build_cancel_negated_addend_2},
    {"cancel-negated-x0",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_negated_x0,
     build_cancel_negated_x0},
    {"cancel-negated-zero-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_cancel_negated_zero_plus_one,
     build_cancel_negated_zero_plus_one},
    {"cancel-negative-one-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_negative_one_and_one,
     build_cancel_negative_one_and_one},
    {"cancel-negative-one-offset",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_negative_one_offset,
     build_cancel_negative_one_offset},
    {"cancel-nested-add",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_nested_add,
     build_cancel_nested_add},
    {"cancel-not-zero-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_cancel_not_zero_plus_one,
     build_cancel_not_zero_plus_one},
    {"cancel-one-minus",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_cancel_one_minus,
     build_cancel_one_minus},
    {"cancel-one-plus-all-ones",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_one_plus_all_ones,
     build_cancel_one_plus_all_ones},
    {"cancel-shifted-addend",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::BV_ADD,
     true,
     match_cancel_shifted_addend,
     build_cancel_shifted_addend},
    {"cancel-shift-and-complement",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_cancel_shift_and_complement,
     build_cancel_shift_and_complement},
    {"cancel-xor-complement-offset",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_cancel_xor_complement_offset,
     build_cancel_xor_complement_offset},
    {"carry-increment-add-complements",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_carry_increment_add_complements,
     build_carry_increment_add_complements},
    {"collapse-additive-constants",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_additive_constants,
     build_collapse_additive_constants},
    {"collapse-additive-constants-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_additive_constants_2,
     build_collapse_additive_constants_2},
    {"collapse-all-ones-addition",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_all_ones_addition,
     build_collapse_all_ones_addition},
    {"collapse-complemented-addends",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_complemented_addends,
     build_collapse_complemented_addends},
    {"collapse-complemented-addends-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_collapse_complemented_addends_2,
     build_collapse_complemented_addends_2},
    {"collapse-complemented-addends-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_collapse_complemented_addends_3,
     build_collapse_complemented_addends_3},
    {"collapse-complemented-addends-4",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_collapse_complemented_addends_4,
     build_collapse_complemented_addends_4},
    {"collapse-complemented-zero-addend",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_collapse_complemented_zero_addend,
     build_collapse_complemented_zero_addend},
    {"collapse-complement-and-one",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_complement_and_one,
     build_collapse_complement_and_one},
    {"collapse-complement-subtraction",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_collapse_complement_subtraction,
     build_collapse_complement_subtraction},
    {"collapse-minus-one-addends-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_collapse_minus_one_addends_2,
     build_collapse_minus_one_addends_2},
    {"collapse-minus-one-addition",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_collapse_minus_one_addition,
     build_collapse_minus_one_addition},
    {"collapse-not-zero-plus-one",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_collapse_not_zero_plus_one,
     build_collapse_not_zero_plus_one},
    {"collapse-ones-complement-addition",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_collapse_ones_complement_addition,
     build_collapse_ones_complement_addition},
    {"combine-added-constants",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_combine_added_constants,
     build_combine_added_constants},
    {"combine-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_addends,
     build_combine_addends},
    {"combine-addends-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_combine_addends_2,
     build_combine_addends_2},
    {"combine-addends-and-constants",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_combine_addends_and_constants,
     build_combine_addends_and_constants},
    {"combine-addends-and-constants-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_addends_and_constants_2,
     build_combine_addends_and_constants_2},
    {"combine-addends-before-arithmetic-shift",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_combine_addends_before_arithmetic_shift,
     build_combine_addends_before_arithmetic_shift},
    {"combine-addends-before-arithmetic-shift-2",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_combine_addends_before_arithmetic_shift_2,
     build_combine_addends_before_arithmetic_shift_2},
    {"combine-additive-constants",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_additive_constants,
     build_combine_additive_constants},
    {"combine-additive-constants-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_additive_constants_2,
     build_combine_additive_constants_2},
    {"combine-all-ones-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_all_ones_addends,
     build_combine_all_ones_addends},
    {"combine-bvadd-constants",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_bvadd_constants,
     build_combine_bvadd_constants},
    {"combine-canceling-offsets",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_canceling_offsets,
     build_combine_canceling_offsets},
    {"combine-complemented-addends-2",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_complemented_addends_2,
     build_combine_complemented_addends_2},
    {"combine-complemented-addends-3",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_NOT,
     true,
     match_combine_complemented_addends_3,
     build_combine_complemented_addends_3},
    {"combine-complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_combine_complemented_sum,
     build_combine_complemented_sum},
    {"combine-constant-addends",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_combine_constant_addends,
     build_combine_constant_addends},
    {"combine-duplicate-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_duplicate_addends,
     build_combine_duplicate_addends},
    {"combine-increment-and-complement",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_increment_and_complement,
     build_combine_increment_and_complement},
    {"combine-nested-adds",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_combine_nested_adds,
     build_combine_nested_adds},
    {"combine-offset-additions",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_combine_offset_additions,
     build_combine_offset_additions},
    {"complemented-incremented-sum",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_complemented_incremented_sum,
     build_complemented_incremented_sum},
    {"complemented-incremented-sum-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_NOT,
     true,
     match_complemented_incremented_sum_2,
     build_complemented_incremented_sum_2},
    {"complemented-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_complemented_sum,
     build_complemented_sum},
    {"complemented-sum-negation",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_complemented_sum_negation,
     build_complemented_sum_negation},
    {"complemented-sum-to-offset-subtraction",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_complemented_sum_to_offset_subtraction,
     build_complemented_sum_to_offset_subtraction},
    {"contradictory-boolean-conjunction",
     Kind::AND,
     Kind::NOT,
     Kind::AND,
     true,
     match_contradictory_boolean_conjunction,
     build_contradictory_boolean_conjunction},
    {"contradictory-boolean-conjunction-2",
     Kind::AND,
     Kind::NOT,
     Kind::AND,
     true,
     match_contradictory_boolean_conjunction_2,
     build_contradictory_boolean_conjunction_2},
    {"contradictory-equality",
     Kind::AND,
     Kind::AND,
     Kind::EQUAL,
     true,
     match_contradictory_equality,
     build_contradictory_equality},
    {"contradictory-zero-test",
     Kind::AND,
     Kind::NOT,
     Kind::AND,
     true,
     match_contradictory_zero_test,
     build_contradictory_zero_test},
    {"double-bitwise-negation-sum",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_double_bitwise_negation_sum,
     build_double_bitwise_negation_sum},
    {"double-negated-sum-complement",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_double_negated_sum_complement,
     build_double_negated_sum_complement},
    {"factor-bitwise-and",
     Kind::BV_AND,
     Kind::BV_AND,
     Kind::NULL_NODE,
     true,
     match_factor_bitwise_and,
     build_factor_bitwise_and},
    {"factor-common-bitvector-multiplier-2",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_MUL,
     true,
     match_factor_common_bitvector_multiplier_2,
     build_factor_common_bitvector_multiplier_2},
    {"factor-common-bit-vector-multiplicand",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_bit_vector_multiplicand,
     build_factor_common_bit_vector_multiplicand},
    {"factor-common-bv-mul",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_bv_mul,
     build_factor_common_bv_mul},
    {"factor-common-bv-multiply",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_bv_multiply,
     build_factor_common_bv_multiply},
    {"factor-common-multiplicand",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand,
     build_factor_common_multiplicand},
    {"factor-common-multiplicand-10",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_10,
     build_factor_common_multiplicand_10},
    {"factor-common-multiplicand-2",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_2,
     build_factor_common_multiplicand_2},
    {"factor-common-multiplicand-3",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_3,
     build_factor_common_multiplicand_3},
    {"factor-common-multiplicand-4",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_4,
     build_factor_common_multiplicand_4},
    {"factor-common-multiplicand-5",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_factor_common_multiplicand_5,
     build_factor_common_multiplicand_5},
    {"factor-common-multiplicand-6",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_6,
     build_factor_common_multiplicand_6},
    {"factor-common-multiplicand-7",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_7,
     build_factor_common_multiplicand_7},
    {"factor-common-multiplicand-8",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplicand_8,
     build_factor_common_multiplicand_8},
    {"factor-common-multiplicand-9",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_MUL,
     true,
     match_factor_common_multiplicand_9,
     build_factor_common_multiplicand_9},
    {"factor-common-multiplier",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplier,
     build_factor_common_multiplier},
    {"factor-common-multiplier-3",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplier_3,
     build_factor_common_multiplier_3},
    {"factor-common-multiplier-4",
     Kind::BV_ADD,
     Kind::BV_MUL,
     Kind::BV_ADD,
     true,
     match_factor_common_multiplier_4,
     build_factor_common_multiplier_4},
    {"factor-common-multiplier-5",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_factor_common_multiplier_5,
     build_factor_common_multiplier_5},
    {"factor-shared-bitwise-and",
     Kind::BV_AND,
     Kind::BV_AND,
     Kind::BV_AND,
     true,
     match_factor_shared_bitwise_and,
     build_factor_shared_bitwise_and},
    {"factor-shared-xor-mask",
     Kind::BV_XOR,
     Kind::BV_AND,
     Kind::BV_XOR,
     true,
     match_factor_shared_xor_mask,
     build_factor_shared_xor_mask},
    {"flatten-bitvector-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_flatten_bitvector_sum,
     build_flatten_bitvector_sum},
    {"flatten-bvadd-and-cancel-ones",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_flatten_bvadd_and_cancel_ones,
     build_flatten_bvadd_and_cancel_ones},
    {"flatten-bvadd-constants",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_flatten_bvadd_constants,
     build_flatten_bvadd_constants},
    {"fold-additive-constants-before-not",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_fold_additive_constants_before_not,
     build_fold_additive_constants_before_not},
    {"fold-additive-offsets",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_additive_offsets,
     build_fold_additive_offsets},
    {"fold-arithmetic-offsets-before-arithmetic-shift",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_fold_arithmetic_offsets_before_arithmetic_shift,
     build_fold_arithmetic_offsets_before_arithmetic_shift},
    {"fold-bitvector-offsets",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_bitvector_offsets,
     build_fold_bitvector_offsets},
    {"fold-bvadd-bvnot-constants",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_fold_bvadd_bvnot_constants,
     build_fold_bvadd_bvnot_constants},
    {"fold-cancelled-addends-before-arithmetic-shift",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     true,
     match_fold_cancelled_addends_before_arithmetic_shift,
     build_fold_cancelled_addends_before_arithmetic_shift},
    {"fold-complemented-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_complemented_addends,
     build_fold_complemented_addends},
    {"fold-complemented-addition",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_fold_complemented_addition,
     build_fold_complemented_addition},
    {"fold-minus-one-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_minus_one_and_one,
     build_fold_minus_one_and_one},
    {"fold-minus-one-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_minus_one_plus_one,
     build_fold_minus_one_plus_one},
    {"fold-minus-one-plus-one-2",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_fold_minus_one_plus_one_2,
     build_fold_minus_one_plus_one_2},
    {"fold-negated-increment",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_fold_negated_increment,
     build_fold_negated_increment},
    {"fold-negative-one-addition",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_fold_negative_one_addition,
     build_fold_negative_one_addition},
    {"fold-negative-one-and-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_fold_negative_one_and_one,
     build_fold_negative_one_and_one},
    {"grouped-add-complement-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_grouped_add_complement_sum,
     build_grouped_add_complement_sum},
    {"invert-decrement-equality",
     Kind::AND,
     Kind::NULL_NODE,
     Kind::AND,
     true,
     match_invert_decrement_equality,
     build_invert_decrement_equality},
    {"merge-negated-addends",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_NOT,
     true,
     match_merge_negated_addends,
     build_merge_negated_addends},
    {"move-complemented-addend-across-equality",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_move_complemented_addend_across_equality,
     build_move_complemented_addend_across_equality},
    {"move-negated-addend",
     Kind::EQUAL,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_move_negated_addend,
     build_move_negated_addend},
    {"negated-difference-arithmetic-shift",
     Kind::BV_NOT,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     false,
     match_negated_difference_arithmetic_shift,
     build_negated_difference_arithmetic_shift},
    {"negated-sum-and",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_negated_sum_and,
     build_negated_sum_and},
    {"negated-sum-complement",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::BV_ADD,
     true,
     match_negated_sum_complement,
     build_negated_sum_complement},
    {"negated-sum-reassociation",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_NOT,
     true,
     match_negated_sum_reassociation,
     build_negated_sum_reassociation},
    {"normalize-addition-and-complement",
     Kind::NOT,
     Kind::EQUAL,
     Kind::NULL_NODE,
     false,
     match_normalize_addition_and_complement,
     build_normalize_addition_and_complement},
    {"normalize-add-negated-sum",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_normalize_add_negated_sum,
     build_normalize_add_negated_sum},
    {"normalize-arithmetic-shift-expression",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::BV_ADD,
     true,
     match_normalize_arithmetic_shift_expression,
     build_normalize_arithmetic_shift_expression},
    {"not-ashr-add-one",
     Kind::BV_NOT,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     false,
     match_not_ashr_add_one,
     build_not_ashr_add_one},
    {"not-of-three-way-sum",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_not_of_three_way_sum,
     build_not_of_three_way_sum},
    {"not-sum-via-complement",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_not_sum_via_complement,
     build_not_sum_via_complement},
    {"reassociate-complemented-sum",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_reassociate_complemented_sum,
     build_reassociate_complemented_sum},
    {"remove-negative-one-addend",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_remove_negative_one_addend,
     build_remove_negative_one_addend},
    {"remove-zero-plus-one",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_remove_zero_plus_one,
     build_remove_zero_plus_one},
    {"signed-half-plus-low-bit",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_signed_half_plus_low_bit,
     build_signed_half_plus_low_bit},
    {"signed-positive-increment-sum-2",
     Kind::BV_SLT,
     Kind::VALUE,
     Kind::BV_ADD,
     false,
     match_signed_positive_increment_sum_2,
     build_signed_positive_increment_sum_2},
    {"signed-positive-of-sum-plus-one",
     Kind::BV_SLT,
     Kind::VALUE,
     Kind::BV_ADD,
     false,
     match_signed_positive_of_sum_plus_one,
     build_signed_positive_of_sum_plus_one},
    {"simplify-additive-complements",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_simplify_additive_complements,
     build_simplify_additive_complements},
    {"simplify-add-before-arithmetic-shift",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_add_before_arithmetic_shift,
     build_simplify_add_before_arithmetic_shift},
    {"simplify-add-complement-cancellation",
     Kind::BV_XOR,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     true,
     match_simplify_add_complement_cancellation,
     build_simplify_add_complement_cancellation},
    {"simplify-add-negated-one",
     Kind::BV_NOT,
     Kind::BV_XOR,
     Kind::NULL_NODE,
     false,
     match_simplify_add_negated_one,
     build_simplify_add_negated_one},
    {"simplify-add-negated-zero-offsets",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_simplify_add_negated_zero_offsets,
     build_simplify_add_negated_zero_offsets},
    {"simplify-all-ones-addition",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::BV_ADD,
     true,
     match_simplify_all_ones_addition,
     build_simplify_all_ones_addition},
    {"simplify-arithmetic-shifted-sum",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ASHR,
     true,
     match_simplify_arithmetic_shifted_sum,
     build_simplify_arithmetic_shifted_sum},
    {"simplify-arithmetic-shift-bias",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ASHR,
     true,
     match_simplify_arithmetic_shift_bias,
     build_simplify_arithmetic_shift_bias},
    {"simplify-arithmetic-shift-expression",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_arithmetic_shift_expression,
     build_simplify_arithmetic_shift_expression},
    {"simplify-arithmetic-shift-sum",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_arithmetic_shift_sum,
     build_simplify_arithmetic_shift_sum},
    {"simplify-complemented-add",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::NULL_NODE,
     true,
     match_simplify_complemented_add,
     build_simplify_complemented_add},
    {"simplify-complemented-subtraction",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_simplify_complemented_subtraction,
     build_simplify_complemented_subtraction},
    {"simplify-complemented-sum",
     Kind::BV_SLT,
     Kind::VALUE,
     Kind::BV_ADD,
     false,
     match_simplify_complemented_sum,
     build_simplify_complemented_sum},
    {"simplify-complemented-sum-shift",
     Kind::BV_NOT,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     false,
     match_simplify_complemented_sum_shift,
     build_simplify_complemented_sum_shift},
    {"simplify-negated-addends",
     Kind::BV_ADD,
     Kind::VALUE,
     Kind::BV_ADD,
     true,
     match_simplify_negated_addends,
     build_simplify_negated_addends},
    {"simplify-negated-add-ones",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_simplify_negated_add_ones,
     build_simplify_negated_add_ones},
    {"simplify-negated-arithmetic-shift",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     true,
     match_simplify_negated_arithmetic_shift,
     build_simplify_negated_arithmetic_shift},
    {"simplify-negated-arithmetic-shift-2",
     Kind::BV_ADD,
     Kind::BV_NOT,
     Kind::VALUE,
     true,
     match_simplify_negated_arithmetic_shift_2,
     build_simplify_negated_arithmetic_shift_2},
    {"simplify-negated-shifted-sum",
     Kind::BV_NOT,
     Kind::BV_ASHR,
     Kind::NULL_NODE,
     false,
     match_simplify_negated_shifted_sum,
     build_simplify_negated_shifted_sum},
    {"simplify-negated-zero-addends",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_negated_zero_addends,
     build_simplify_negated_zero_addends},
    {"simplify-negative-shifted-complement",
     Kind::BV_ADD,
     Kind::BV_ASHR,
     Kind::BV_ADD,
     true,
     match_simplify_negative_shifted_complement,
     build_simplify_negative_shifted_complement},
    {"simplify-nested-bvadd",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_nested_bvadd,
     build_simplify_nested_bvadd},
    {"simplify-nested-complement-add",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_NOT,
     true,
     match_simplify_nested_complement_add,
     build_simplify_nested_complement_add},
    {"simplify-not-add-negated-shift",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_simplify_not_add_negated_shift,
     build_simplify_not_add_negated_shift},
    {"simplify-offset-sum-arithmetic-shift",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_offset_sum_arithmetic_shift,
     build_simplify_offset_sum_arithmetic_shift},
    {"simplify-shifted-double-add",
     Kind::BV_ASHR,
     Kind::BV_ADD,
     Kind::VALUE,
     false,
     match_simplify_shifted_double_add,
     build_simplify_shifted_double_add},
    {"subtraction-via-complemented-addition",
     Kind::BV_ADD,
     Kind::BV_ADD,
     Kind::VALUE,
     true,
     match_subtraction_via_complemented_addition,
     build_subtraction_via_complemented_addition},
    {"xor-and-distribution-factor",
     Kind::BV_XOR,
     Kind::BV_AND,
     Kind::BV_XOR,
     true,
     match_xor_and_distribution_factor,
     build_xor_and_distribution_factor},
    {"xor-complement-add-to-sub",
     Kind::BV_ADD,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_xor_complement_add_to_sub,
     build_xor_complement_add_to_sub},
    {"xor-mask-combine",
     Kind::BV_XOR,
     Kind::BV_XOR,
     Kind::BV_AND,
     true,
     match_xor_mask_combine,
     build_xor_mask_combine},
    {"xor-mux-distribution",
     Kind::BV_XOR,
     Kind::BV_AND,
     Kind::BV_XOR,
     true,
     match_xor_mux_distribution,
     build_xor_mux_distribution},
    {"xor-negated-decrement",
     Kind::BV_XOR,
     Kind::NULL_NODE,
     Kind::BV_ADD,
     true,
     match_xor_negated_decrement,
     build_xor_negated_decrement},
    {"xor-negation-add-rewrite",
     Kind::BV_NOT,
     Kind::BV_ADD,
     Kind::NULL_NODE,
     false,
     match_xor_negation_add_rewrite,
     build_xor_negation_add_rewrite},
    {"xor-not-decrement-pattern",
     Kind::BV_XOR,
     Kind::NULL_NODE,
     Kind::BV_AND,
     true,
     match_xor_not_decrement_pattern,
     build_xor_not_decrement_pattern},
    {"xor-subtract-one-equality",
     Kind::EQUAL,
     Kind::BV_XOR,
     Kind::NULL_NODE,
     true,
     match_xor_subtract_one_equality,
     build_xor_subtract_one_equality},
    {"zero-after-left-shift",
     Kind::EQUAL,
     Kind::VALUE,
     Kind::BV_SHL,
     true,
     match_zero_after_left_shift,
     build_zero_after_left_shift},
};

static_assert(sizeof(s_rules) / sizeof(s_rules[0])
              == static_cast<size_t>(RareRuleKind::NUM_RULES));

/** The rules in order of priority. */
const RareRuleKind s_priority[] = {
    RareRuleKind::COLLAPSE_MINUS_ONE_ADDITION,
    RareRuleKind::COMBINE_DUPLICATE_ADDENDS,
    RareRuleKind::FACTOR_SHARED_XOR_MASK,
    RareRuleKind::AVERAGE_FLOOR_SIGNED_SUM,
    RareRuleKind::BVADD_NEGATED_SHIFT_CANCELLATION,
    RareRuleKind::CANCEL_SHIFT_AND_COMPLEMENT,
    RareRuleKind::CANCEL_COMPLEMENTED_SUM,
    RareRuleKind::CANCEL_SHIFTED_ADDEND,
    RareRuleKind::CONTRADICTORY_ZERO_TEST,
    RareRuleKind::CANCEL_ADD_COMPLEMENT,
    RareRuleKind::CONTRADICTORY_EQUALITY,
    RareRuleKind::FACTOR_SHARED_BITWISE_AND,
    RareRuleKind::ASHR_HALF_SUM_FOLD,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_4,
    RareRuleKind::BVADD_MINUS_ONE_CANCEL,
    RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_3,
    RareRuleKind::CANCEL_ALL_ONES_AND_ONE_3,
    RareRuleKind::COMBINE_ADDENDS_BEFORE_ARITHMETIC_SHIFT,
    RareRuleKind::COMBINE_ADDENDS_BEFORE_ARITHMETIC_SHIFT_2,
    RareRuleKind::FOLD_NEGATIVE_ONE_ADDITION,
    RareRuleKind::REMOVE_NEGATIVE_ONE_ADDEND,
    RareRuleKind::SIMPLIFY_ALL_ONES_ADDITION,
    RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_EXPRESSION,
    RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_SUM,
    RareRuleKind::SIMPLIFY_NESTED_BVADD,
    RareRuleKind::SIMPLIFY_SHIFTED_DOUBLE_ADD,
    RareRuleKind::ADD_ALL_ONES_CANCEL,
    RareRuleKind::ADDITIVE_CANCEL_ONES,
    RareRuleKind::ASHR_SIMPLIFY_ADD_CANCEL,
    RareRuleKind::ASHR_SUM_AFTER_CANCELLED_OFFSET,
    RareRuleKind::ASHR_SUM_CANCEL_ONES,
    RareRuleKind::ASHR_SUM_MINUS_ONE_HALF,
    RareRuleKind::ASHR_SUM_OFFSET_CANCEL,
    RareRuleKind::BV_ADD_MINUS_ONE_OFFSET,
    RareRuleKind::BVADD_ALL_ONES_AS_MINUS_ONE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_PLUS_ONE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_WITH_ONE,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE_3,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE_3,
    RareRuleKind::BVADD_CANCEL_NEGATIVE_ONE_AND_ONE,
    RareRuleKind::BVADD_CANCEL_OFFSETS,
    RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_2,
    RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_4,
    RareRuleKind::BVADD_NEG_ONE_AND_ONE_CANCEL,
    RareRuleKind::BVADD_NEG_ONE_CANCEL,
    RareRuleKind::BVADD_NEG_ONE_CANCEL_3,
    RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCEL,
    RareRuleKind::BVASHR_CANCEL_ADDITIVE_CONSTANTS,
    RareRuleKind::BVNOT_ZERO_ADD_CANCEL,
    RareRuleKind::BVNOT_ZERO_PLUS_ONE,
    RareRuleKind::CANCEL_ADDITIVE_CONSTANTS_BEFORE_ARITHMETIC_SHIFT,
    RareRuleKind::CANCEL_ALL_ONES_ADDENDS,
    RareRuleKind::CANCEL_ALL_ONES_OFFSET,
    RareRuleKind::CANCEL_ALL_ONES_PLUS_ONE,
    RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE,
    RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE_3,
    RareRuleKind::CANCEL_MODULAR_OFFSETS,
    RareRuleKind::COLLAPSE_ADDITIVE_CONSTANTS,
    RareRuleKind::COLLAPSE_COMPLEMENTED_ZERO_ADDEND,
    RareRuleKind::COLLAPSE_MINUS_ONE_ADDENDS_2,
    RareRuleKind::COLLAPSE_ONES_COMPLEMENT_ADDITION,
    RareRuleKind::COMBINE_ADDED_CONSTANTS,
    RareRuleKind::COMBINE_ADDENDS_2,
    RareRuleKind::COMBINE_ADDENDS_AND_CONSTANTS,
    RareRuleKind::COMBINE_ADDENDS_AND_CONSTANTS_2,
    RareRuleKind::COMBINE_ADDITIVE_CONSTANTS,
    RareRuleKind::COMBINE_ADDITIVE_CONSTANTS_2,
    RareRuleKind::COMBINE_ALL_ONES_ADDENDS,
    RareRuleKind::COMBINE_BVADD_CONSTANTS,
    RareRuleKind::COMBINE_CONSTANT_ADDENDS,
    RareRuleKind::COMBINE_OFFSET_ADDITIONS,
    RareRuleKind::FLATTEN_BITVECTOR_SUM,
    RareRuleKind::FLATTEN_BVADD_AND_CANCEL_ONES,
    RareRuleKind::FLATTEN_BVADD_CONSTANTS,
    RareRuleKind::FOLD_ARITHMETIC_OFFSETS_BEFORE_ARITHMETIC_SHIFT,
    RareRuleKind::FOLD_BITVECTOR_OFFSETS,
    RareRuleKind::FOLD_CANCELLED_ADDENDS_BEFORE_ARITHMETIC_SHIFT,
    RareRuleKind::FOLD_MINUS_ONE_AND_ONE,
    RareRuleKind::FOLD_NEGATIVE_ONE_AND_ONE,
    RareRuleKind::REMOVE_ZERO_PLUS_ONE,
    RareRuleKind::SIMPLIFY_ADD_NEGATED_ZERO_OFFSETS,
    RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_BIAS,
    RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFTED_SUM,
    RareRuleKind::SIMPLIFY_OFFSET_SUM_ARITHMETIC_SHIFT,
    RareRuleKind::BV_ADD_ALL_ONES_CANCEL,
    RareRuleKind::BVADD_ALLONES_EQUALITY_REVERSE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE_2,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE_3,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_2,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_3,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_2,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_3,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_4,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE_2,
    RareRuleKind::BVADD_CANCEL_NEG_ONE_AND_ONE_2,
    RareRuleKind::BVADD_CANCEL_NEGATIVE_ONE,
    RareRuleKind::BVADD_CANCEL_ONE_MINUS_ONE,
    RareRuleKind::BVADD_CANCEL_ONE_MINUS_ONE_2,
    RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_5,
    RareRuleKind::BVADD_NEGATED_ZERO_OFFSET,
    RareRuleKind::BVADD_ONE_AS_NEGATED_COMPLEMENT,
    RareRuleKind::BVADD_ONE_COMPLEMENT_MINUS_ONE,
    RareRuleKind::BVADD_REASSOCIATE_COMPLEMENT,
    RareRuleKind::BVAND_EQUALITY_IDEMPOTENCE,
    RareRuleKind::BVNOT_ZERO_ADD_IDENTITY_2,
    RareRuleKind::CANCEL_ADD_ONE_AND_ALL_ONES,
    RareRuleKind::CANCEL_ALL_ONES_AND_ONE,
    RareRuleKind::CANCEL_ALL_ONES_OFFSET_2,
    RareRuleKind::CANCEL_ALL_ONES_PLUS_ONE_2,
    RareRuleKind::CANCEL_BV_NEGATED_ZERO_OFFSET,
    RareRuleKind::CANCEL_COMPLEMENTED_ZERO_AND_ONE,
    RareRuleKind::CANCEL_MINUS_ONE_OFFSET,
    RareRuleKind::CANCEL_MINUS_ONE_OFFSET_2,
    RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE_2,
    RareRuleKind::CANCEL_NEGATED_ZERO_PLUS_ONE,
    RareRuleKind::CANCEL_NOT_ZERO_PLUS_ONE,
    RareRuleKind::CARRY_INCREMENT_ADD_COMPLEMENTS,
    RareRuleKind::COLLAPSE_COMPLEMENT_AND_ONE,
    RareRuleKind::COMBINE_ADDENDS,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_6,
    RareRuleKind::FACTOR_COMMON_MULTIPLIER_4,
    RareRuleKind::FOLD_ADDITIVE_OFFSETS,
    RareRuleKind::FOLD_MINUS_ONE_PLUS_ONE,
    RareRuleKind::FOLD_MINUS_ONE_PLUS_ONE_2,
    RareRuleKind::SIGNED_POSITIVE_INCREMENT_SUM_2,
    RareRuleKind::SIGNED_POSITIVE_OF_SUM_PLUS_ONE,
    RareRuleKind::XOR_AND_DISTRIBUTION_FACTOR,
    RareRuleKind::XOR_MASK_COMBINE,
    RareRuleKind::ADD_ONE_VIA_COMPLEMENTED_SUM,
    RareRuleKind::BV_COMPLEMENT_PLUS_X_TO_INCREMENT,
    RareRuleKind::BVADD_COMBINE_COMPLEMENTED_PAIR,
    RareRuleKind::BVADD_ONE_AS_COMPLEMENT,
    RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALS_SUCCESSOR,
    RareRuleKind::FACTOR_COMMON_BIT_VECTOR_MULTIPLICAND,
    RareRuleKind::FACTOR_COMMON_BV_MUL,
    RareRuleKind::FACTOR_COMMON_BV_MULTIPLY,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_10,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_2,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_3,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_4,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_7,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_8,
    RareRuleKind::FACTOR_COMMON_MULTIPLIER,
    RareRuleKind::FACTOR_COMMON_MULTIPLIER_3,
    RareRuleKind::FACTOR_COMMON_MULTIPLIER_5,
    RareRuleKind::INVERT_DECREMENT_EQUALITY,
    RareRuleKind::ASHR_SUBTRACT_ONE_COMPLEMENT,
    RareRuleKind::BVADD_CANCEL_NEGATED_ZERO,
    RareRuleKind::BVADD_FOLD_MINUS_ONE,
    RareRuleKind::BVADD_NEGATED_X1_AND_ARITHMETIC_SHIFT,
    RareRuleKind::BVADD_NOT_SUBTRACT_SIMPLIFICATION,
    RareRuleKind::BVADD_ONES_AND_INCREMENT_CANCEL,
    RareRuleKind::BVNOT_ADD_CANCEL_ONE,
    RareRuleKind::BVNOT_ADD_SUM_COMPLEMENT,
    RareRuleKind::BVNOT_MINUS_ONE_ADD,
    RareRuleKind::CANCEL_COMPLEMENTED_ADDEND,
    RareRuleKind::CANCEL_MINUS_ONE_AND_ONE,
    RareRuleKind::FOLD_BVADD_BVNOT_CONSTANTS,
    RareRuleKind::NORMALIZE_ARITHMETIC_SHIFT_EXPRESSION,
    RareRuleKind::SIGNED_HALF_PLUS_LOW_BIT,
    RareRuleKind::SIMPLIFY_COMPLEMENTED_SUM_SHIFT,
    RareRuleKind::SIMPLIFY_NEGATED_ADDENDS,
    RareRuleKind::SIMPLIFY_NEGATED_SHIFTED_SUM,
    RareRuleKind::SIMPLIFY_NEGATED_ZERO_ADDENDS,
    RareRuleKind::ADD_NOT_SUM_WITH_OFFSET,
    RareRuleKind::ASHR_NEGATED_SUM_SPLIT,
    RareRuleKind::BV_NEGATED_SUM_EXPRESSION,
    RareRuleKind::BVADD_ALL_ONES_CANCEL_ONE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_2,
    RareRuleKind::BVADD_CANCEL_COMPLEMENT_4,
    RareRuleKind::BVADD_CANCEL_ONES,
    RareRuleKind::BVADD_CARRY_CONSTANT_FOLD,
    RareRuleKind::BVADD_COMPLEMENT_SUM,
    RareRuleKind::BVADD_FOLD_NEGATED_ONE,
    RareRuleKind::BVADD_MINUS_ONE_SUBTRACTION,
    RareRuleKind::BVADD_NOT_SUM_PLUS_ONE,
    RareRuleKind::BVADD_NOT_ZERO_COLLAPSE,
    RareRuleKind::BVNOT_ADD_NORMALIZE,
    RareRuleKind::BVNOT_ADD_ONE_COLLAPSE,
    RareRuleKind::BVNOT_ADD_SPLIT,
    RareRuleKind::BVNOT_ADD_SUCCESSOR,
    RareRuleKind::BVNOT_ADD_ZERO_MINUS_ONE_3,
    RareRuleKind::BVNOT_SUM_WITH_INCREMENTS,
    RareRuleKind::CANCEL_ADD_AND_COMPLEMENT,
    RareRuleKind::CANCEL_ADD_ONE_FROM_COMPLEMENTED_SUM,
    RareRuleKind::CANCEL_ADDITIVE_COMPLEMENT,
    RareRuleKind::CANCEL_ADDITIVE_CONSTANTS,
    RareRuleKind::CANCEL_ADDITIVE_INVERSES_SIGNED_LT,
    RareRuleKind::CANCEL_ADDITIVE_NEGATION,
    RareRuleKind::CANCEL_ALL_ONES_ADDEND,
    RareRuleKind::CANCEL_COMPLEMENT_INCREMENT,
    RareRuleKind::CANCEL_NEGATED_ADDEND_2,
    RareRuleKind::CANCEL_NEGATED_X0,
    RareRuleKind::CANCEL_XOR_COMPLEMENT_OFFSET,
    RareRuleKind::COLLAPSE_ADDITIVE_CONSTANTS_2,
    RareRuleKind::COLLAPSE_COMPLEMENT_SUBTRACTION,
    RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_2,
    RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_3,
    RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_4,
    RareRuleKind::COMBINE_INCREMENT_AND_COMPLEMENT,
    RareRuleKind::COMPLEMENTED_INCREMENTED_SUM_2,
    RareRuleKind::CONTRADICTORY_BOOLEAN_CONJUNCTION,
    RareRuleKind::CONTRADICTORY_BOOLEAN_CONJUNCTION_2,
    RareRuleKind::FOLD_ADDITIVE_CONSTANTS_BEFORE_NOT,
    RareRuleKind::FOLD_COMPLEMENTED_ADDENDS,
    RareRuleKind::FOLD_NEGATED_INCREMENT,
    RareRuleKind::MOVE_NEGATED_ADDEND,
    RareRuleKind::NORMALIZE_ADDITION_AND_COMPLEMENT,
    RareRuleKind::NOT_OF_THREE_WAY_SUM,
    RareRuleKind::SIMPLIFY_ADD_COMPLEMENT_CANCELLATION,
    RareRuleKind::SIMPLIFY_ADD_NEGATED_ONE,
    RareRuleKind::SIMPLIFY_ADDITIVE_COMPLEMENTS,
    RareRuleKind::SIMPLIFY_COMPLEMENTED_ADD,
    RareRuleKind::SIMPLIFY_COMPLEMENTED_SUM,
    RareRuleKind::SIMPLIFY_NEGATED_ADD_ONES,
    RareRuleKind::SIMPLIFY_NEGATIVE_SHIFTED_COMPLEMENT,
    RareRuleKind::XOR_NEGATED_DECREMENT,
    RareRuleKind::BVADD_CANCEL_COMPLEMENTED_SUMMAND,
    RareRuleKind::BVADD_NOT_AND_TO_NOT_SUM,
    RareRuleKind::BVAND_DISTRIBUTE_INVERTED_FACTOR,
    RareRuleKind::BVNOT_ADD_ONE_SIMPLIFY,
    RareRuleKind::BVNOT_SUM_DISTRIBUTE,
    RareRuleKind::BVNOT_SUM_GROUPED_NEGATIONS,
    RareRuleKind::BVNOT_ZERO_ADD_EQUALITY,
    RareRuleKind::BVNOT_ZERO_ADD_INVERT,
    RareRuleKind::BVNOT_ZERO_ADD_ONE_REASSOCIATE,
    RareRuleKind::BVNOT_ZERO_ADD_REVERSE,
    RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALITY,
    RareRuleKind::CANCEL_NESTED_ADD,
    RareRuleKind::MOVE_COMPLEMENTED_ADDEND_ACROSS_EQUALITY,
    RareRuleKind::NORMALIZE_ADD_NEGATED_SUM,
    RareRuleKind::SIMPLIFY_NEGATED_ARITHMETIC_SHIFT_2,
    RareRuleKind::XOR_NOT_DECREMENT_PATTERN,
    RareRuleKind::BVADD_CANCEL_ALLONES_AND_ONE,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE_2,
    RareRuleKind::BVADD_NEG_ONE_AND_ONE,
    RareRuleKind::BVADD_NEG_ONE_CANCEL_2,
    RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCEL_2,
    RareRuleKind::BVADD_NOT_SUB_CONSTANT,
    RareRuleKind::BVASHR_NEGATED_DIFFERENCE,
    RareRuleKind::BVNOT_ADD_COMPLEMENT,
    RareRuleKind::BVNOT_ADD_IDENTITY,
    RareRuleKind::BVNOT_ADD_MASK_ONE,
    RareRuleKind::BVNOT_SUM_WITH_OFFSET,
    RareRuleKind::BVNOT_ZERO_ADD_ONE_CANCEL,
    RareRuleKind::CANCEL_ADD_INVERSE,
    RareRuleKind::CANCEL_NEGATED_ADDEND,
    RareRuleKind::CANCEL_NEGATIVE_ONE_AND_ONE,
    RareRuleKind::COLLAPSE_ALL_ONES_ADDITION,
    RareRuleKind::COMBINE_CANCELING_OFFSETS,
    RareRuleKind::COMBINE_NESTED_ADDS,
    RareRuleKind::COMPLEMENTED_SUM_TO_OFFSET_SUBTRACTION,
    RareRuleKind::NEGATED_DIFFERENCE_ARITHMETIC_SHIFT,
    RareRuleKind::SIMPLIFY_ADD_BEFORE_ARITHMETIC_SHIFT,
    RareRuleKind::SIMPLIFY_NOT_ADD_NEGATED_SHIFT,
    RareRuleKind::ADD_NEGATED_ZERO_OFFSET,
    RareRuleKind::BV_SUB_INCREMENT_EQUIVALENCE,
    RareRuleKind::BVADD_CANCEL_ALL_ONES_3,
    RareRuleKind::BVADD_CANCEL_ALLONES_PLUS_ONE,
    RareRuleKind::BVADD_CANCEL_MINUS_ONE_OFFSET,
    RareRuleKind::BVADD_CANCEL_NEG_ONE_AND_ONE,
    RareRuleKind::BVADD_CANCEL_OFFSET,
    RareRuleKind::BVADD_COMPLEMENT_REASSOCIATE,
    RareRuleKind::BVADD_COMPLEMENT_SUM_2,
    RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE,
    RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_2,
    RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCELLATION,
    RareRuleKind::BVADD_NEGATED_ZERO_CANCEL,
    RareRuleKind::BVADD_NOT_COMPLEMENT_SUM,
    RareRuleKind::BVADD_NOT_SUM,
    RareRuleKind::BVADD_ONE_EQUALS_BITWISE_DIFFERENCE,
    RareRuleKind::BVAND_CLEAR_BITS,
    RareRuleKind::BVAND_MASK_DISTRIBUTION,
    RareRuleKind::BVNOT_ADD_COMPLEMENTED_AND,
    RareRuleKind::BVNOT_ADD_INVERSE_CANCEL,
    RareRuleKind::BVNOT_ADD_NEGATED_SUM,
    RareRuleKind::BVNOT_ADD_NEGATION_COLLAPSE,
    RareRuleKind::BVNOT_SUM_DIFFERENCE,
    RareRuleKind::CANCEL_ADDITIVE_ONES,
    RareRuleKind::CANCEL_ALL_ONES_AND_ONE_2,
    RareRuleKind::CANCEL_COMPLEMENT_ADDEND,
    RareRuleKind::CANCEL_ONE_MINUS,
    RareRuleKind::CANCEL_ONE_PLUS_ALL_ONES,
    RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS,
    RareRuleKind::COLLAPSE_NOT_ZERO_PLUS_ONE,
    RareRuleKind::COMBINE_COMPLEMENTED_ADDENDS_3,
    RareRuleKind::COMBINE_COMPLEMENTED_SUM,
    RareRuleKind::COMPLEMENTED_SUM_NEGATION,
    RareRuleKind::DOUBLE_NEGATED_SUM_COMPLEMENT,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_5,
    RareRuleKind::FOLD_COMPLEMENTED_ADDITION,
    RareRuleKind::MERGE_NEGATED_ADDENDS,
    RareRuleKind::NEGATED_SUM_AND,
    RareRuleKind::NEGATED_SUM_REASSOCIATION,
    RareRuleKind::NOT_SUM_VIA_COMPLEMENT,
    RareRuleKind::REASSOCIATE_COMPLEMENTED_SUM,
    RareRuleKind::SIMPLIFY_NESTED_COMPLEMENT_ADD,
    RareRuleKind::XOR_NEGATION_ADD_REWRITE,
    RareRuleKind::ADD_ONE_VIA_COMPLEMENTED_SUM_2,
    RareRuleKind::BVADD_ONE_AS_COMPLEMENT_NEGATION,
    RareRuleKind::BVADD_REASSOCIATE_COMPLEMENTED_SUM,
    RareRuleKind::BVNOT_ZERO_ADD_INCREMENT,
    RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALITY_2,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND,
    RareRuleKind::FACTOR_COMMON_MULTIPLICAND_9,
    RareRuleKind::GROUPED_ADD_COMPLEMENT_SUM,
    RareRuleKind::XOR_MUX_DISTRIBUTION,
    RareRuleKind::ASHR_ADD_ONE_NONTRIVIAL,
    RareRuleKind::ASHR_NEGATED_INCREMENT,
    RareRuleKind::ASHR_PLUS_LOW_BIT,
    RareRuleKind::ADD_COMPLEMENT_CANCEL,
    RareRuleKind::ADD_COMPLEMENTED_NEGATION,
    RareRuleKind::ASHR_NEGATED_SUM,
    RareRuleKind::BVADD_CANCEL_ALLONES,
    RareRuleKind::BVADD_COLLAPSE_ALL_ONES,
    RareRuleKind::BVADD_COMPLEMENT_CANCEL,
    RareRuleKind::BVADD_COMPLEMENTED_NEGATION,
    RareRuleKind::BVADD_SUB_CANCELLATION,
    RareRuleKind::BVNOT_ADD_TO_COMPLEMENT_SUM,
    RareRuleKind::BVNOT_SUM_COLLAPSE,
    RareRuleKind::COMPLEMENTED_INCREMENTED_SUM,
    RareRuleKind::DOUBLE_BITWISE_NEGATION_SUM,
    RareRuleKind::NOT_ASHR_ADD_ONE,
    RareRuleKind::SIMPLIFY_COMPLEMENTED_SUBTRACTION,
    RareRuleKind::SIMPLIFY_NEGATED_ARITHMETIC_SHIFT,
    RareRuleKind::BVADD_COMPLEMENT_EQUALITY_XOR,
    RareRuleKind::BVADD_INVERSE_REARRANGE,
    RareRuleKind::BVNOT_ADD_ONE_AND,
    RareRuleKind::BVNOT_ADD_XOR,
    RareRuleKind::BVNOT_ALLONES_ADD_ONE,
    RareRuleKind::BVNOT_INCREMENTED_SUM,
    RareRuleKind::BVNOT_ZERO_ADD_IDENTITY,
    RareRuleKind::CANCELLED_ADDEND,
    RareRuleKind::FACTOR_BITWISE_AND,
    RareRuleKind::XOR_COMPLEMENT_ADD_TO_SUB,
    RareRuleKind::ASHR_COMPLEMENT_ADD_ROUNDING,
    RareRuleKind::BVADD_NEG_ONE_PLUS_ONE,
    RareRuleKind::BVNOT_ADD_NEGATED_SUBTRAHEND,
    RareRuleKind::BVNOT_ADD_NEGATED_SUBTRAHEND_2,
    RareRuleKind::CANCEL_MINUS_ONE_AND_PLUS_ONE,
    RareRuleKind::CANCEL_NEGATIVE_ONE_OFFSET,
    RareRuleKind::COMBINE_COMPLEMENTED_ADDENDS_2,
    RareRuleKind::COMPLEMENTED_SUM,
    RareRuleKind::NEGATED_SUM_COMPLEMENT,
    RareRuleKind::BVADD_ALL_ONES_EQUALS_XOR,
    RareRuleKind::BVADD_MINUS_ONE_EQUALITY,
    RareRuleKind::BVNOT_ZERO_PLUS_INCREMENT_INVERSE,
    RareRuleKind::FACTOR_COMMON_BITVECTOR_MULTIPLIER_2,
    RareRuleKind::XOR_SUBTRACT_ONE_EQUALITY,
    RareRuleKind::ZERO_AFTER_LEFT_SHIFT,
    RareRuleKind::ASHR_COMPLEMENT_NEGATED_INPUT,
    RareRuleKind::ADD_NOT_SUM_CANCEL,
    RareRuleKind::BV_SUB_VIA_NEGATED_OPERANDS,
    RareRuleKind::BVNOT_ADD_PLUS_ONE,
    RareRuleKind::BVNOT_ZERO_ADD_INVERSE,
    RareRuleKind::SUBTRACTION_VIA_COMPLEMENTED_ADDITION,
    RareRuleKind::BVNOT_SUM_COMPLEMENTS,
};

/* --- Rule index ----------------------------------------------------------- */

/** The number of root kinds of match patterns. */
constexpr size_t NUM_ROOTS = 9;
/**
 * The number of head classes, i.e., the number of kinds of children of the
 * root of match patterns, plus one for all other kinds.
 */
constexpr size_t NUM_HEADS = 13;

/** @return The index of the given root kind, NUM_ROOTS if no pattern has this
 * root kind. */
size_t
root_index(Kind kind)
{
  switch (kind)
  {
    case Kind::AND: return 0;
    case Kind::BV_ADD: return 1;
    case Kind::BV_AND: return 2;
    case Kind::BV_ASHR: return 3;
    case Kind::BV_NOT: return 4;
    case Kind::BV_SLT: return 5;
    case Kind::BV_XOR: return 6;
    case Kind::EQUAL: return 7;
    case Kind::NOT: return 8;
    default: return NUM_ROOTS;
  }
}

/** @return The head class of the given kind. */
size_t
head_index(Kind kind)
{
  switch (kind)
  {
    case Kind::AND: return 1;
    case Kind::BV_ADD: return 2;
    case Kind::BV_AND: return 3;
    case Kind::BV_ASHR: return 4;
    case Kind::BV_MUL: return 5;
    case Kind::BV_NOT: return 6;
    case Kind::BV_SHL: return 7;
    case Kind::BV_SLT: return 8;
    case Kind::BV_XOR: return 9;
    case Kind::EQUAL: return 10;
    case Kind::NOT: return 11;
    case Kind::VALUE: return 12;
    default: return 0;
  }
}

/**
 * Index of the rules by the kind of the root and the kinds of the children of
 * the root of their match patterns.
 */
class RuleIndex
{
 public:
  static const RuleIndex& get()
  {
    static const RuleIndex s_index;
    return s_index;
  }

  /** @return The rules (in order of priority) that may match the given node. */
  const std::vector<RareRuleKind>& candidates(const Node& node) const
  {
    size_t root = root_index(node.kind());
    if (root == NUM_ROOTS)
    {
      return d_none;
    }
    size_t h0 = head_index(node[0].kind());
    size_t h1 = node.num_children() > 1 ? head_index(node[1].kind()) : 0;
    return d_candidates[(root * NUM_HEADS + h0) * NUM_HEADS + h1];
  }

 private:
  RuleIndex() : d_candidates(NUM_ROOTS * NUM_HEADS * NUM_HEADS)
  {
    for (RareRuleKind kind : s_priority)
    {
      const RuleInfo& info = s_rules[static_cast<size_t>(kind)];
      size_t root          = root_index(info.root);
      for (size_t h0 = 0; h0 < NUM_HEADS; ++h0)
      {
        for (size_t h1 = 0; h1 < NUM_HEADS; ++h1)
        {
          if ((matches(info.head0, h0) && matches(info.head1, h1))
              || (info.commutative && matches(info.head0, h1)
                  && matches(info.head1, h0)))
          {
            d_candidates[(root * NUM_HEADS + h0) * NUM_HEADS + h1].push_back(
                kind);
          }
        }
      }
    }
  }

  /** @return True if a child of the given head class may match the head. */
  static bool matches(Kind head, size_t index)
  {
    return head == Kind::NULL_NODE || head_index(head) == index;
  }

  std::vector<std::vector<RareRuleKind>> d_candidates;
  const std::vector<RareRuleKind> d_none;
};

}  // namespace

/* --- Public interface ----------------------------------------------------- */

std::ostream&
operator<<(std::ostream& out, RareRuleKind kind)
{
  if (kind == RareRuleKind::NUM_RULES)
  {
    return out << "NUM_RULES";
  }
  return out << s_rules[static_cast<size_t>(kind)].name;
}

const std::vector<RareRuleKind>&
rare_candidates(const Node& node)
{
  return RuleIndex::get().candidates(node);
}

bool
rare_match(RareRuleKind kind, const Node& node, RareMatch& match)
{
  assert(kind != RareRuleKind::NUM_RULES);
  if (s_rules[static_cast<size_t>(kind)].match(node, match.vars.data()))
  {
    match.kind = kind;
    return true;
  }
  return false;
}

Node
rare_build(Rewriter& rewriter, const RareMatch& match)
{
  assert(match.kind != RareRuleKind::NUM_RULES);
  return s_rules[static_cast<size_t>(match.kind)].build(rewriter,
                                                        match.vars.data());
}

}  // namespace bzla
