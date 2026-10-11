/*
 * This file is generated from 363 of the 738 RARE rewrite rules (define-rule)
 * in gpt-6-luna.
 * Do not edit by hand.
 */

#include <algorithm>
#include <cctype>
#include <random>
#include <sstream>

#include "node/node_utils.h"
#include "rewrite/rewrites_rare.h"
#include "test_rewriter.h"

namespace bzla::test {

using namespace node;

class TestRewriterRare : public TestRewriter
{
 protected:
  /** The reason why a rule only applies to bit-vectors of size >= 2. */
  enum class Guard
  {
    /** The rule applies to bit-vectors of any size. */
    NONE,
    /** The rule is not valid for bit-width 1. */
    INVALID,
    /**
     * The built-in rewrite rules rewrite the result (and the match pattern) of
     * the rule at bit-width 1.
     */
    NOT_NORMAL,
  };

  struct Rule
  {
    RareRuleKind kind;
    /** Determines if the rule only applies to bit-vectors of size >= 2. */
    Guard guard;
    /** The parameters of the rule. */
    const char* params;
    /** The match pattern of the rule. */
    const char* lhs;
    /** The rewritten term of the rule. */
    const char* rhs;
  };

  static const std::vector<Rule> s_rules;

  /** S-expression. */
  struct SExpr
  {
    std::string atom;
    std::vector<SExpr> children;
  };

  static SExpr parse_sexpr(const std::string& str)
  {
    std::vector<SExpr> stack(1);
    for (size_t i = 0; i < str.size();)
    {
      char c = str[i];
      if (c == '(')
      {
        stack.emplace_back();
        ++i;
      }
      else if (c == ')')
      {
        SExpr e = std::move(stack.back());
        stack.pop_back();
        stack.back().children.push_back(std::move(e));
        ++i;
      }
      else if (std::isspace(c))
      {
        ++i;
      }
      else
      {
        size_t j = i;
        while (j < str.size() && !std::isspace(str[j]) && str[j] != '('
               && str[j] != ')')
        {
          ++j;
        }
        SExpr e;
        e.atom = str.substr(i, j - i);
        stack.back().children.push_back(std::move(e));
        i = j;
      }
    }
    assert(stack.size() == 1 && stack[0].children.size() == 1);
    return stack[0].children[0];
  }

  /** Instantiation of the variables of a rule at a given bit-width. */
  struct Instance
  {
    uint64_t size;
    std::unordered_map<std::string, Node> vars;
  };

  Instance mk_instance(const Rule& rule, uint64_t size, const std::string& id)
  {
    Instance inst{size, {}};
    SExpr params = parse_sexpr(rule.params);
    for (const SExpr& p : params.children)
    {
      const std::string& name = p.children[0].atom;
      const std::string& sort = p.children[1].atom;
      Type type = sort == "Bool" ? d_nm.mk_bool_type() : d_nm.mk_bv_type(size);
      inst.vars.emplace(name, d_nm.mk_const(type, name + "_" + id));
    }
    return inst;
  }

  /** Evaluate an integer term of a rule. */
  static int64_t eval_int(const SExpr& e, const Instance& inst)
  {
    if (e.children.empty())
    {
      return std::stoll(e.atom);
    }
    const std::string& op = e.children[0].atom;
    if (op == "@bvsize")
    {
      return static_cast<int64_t>(inst.size);
    }
    assert(op == "-");
    int64_t res = eval_int(e.children[1], inst);
    if (e.children.size() == 2)
    {
      return -res;
    }
    for (size_t i = 2; i < e.children.size(); ++i)
    {
      res -= eval_int(e.children[i], inst);
    }
    return res;
  }

  /**
   * Construct the node of a term of a rule (without rewriting). Ground
   * subterms are evaluated if `eval` is true. Children of commutative
   * operators are reversed if `mirror` is true.
   */
  Node mk_term(const SExpr& e,
               const Instance& inst,
               bool eval,
               bool mirror,
               bool& ground)
  {
    static const std::unordered_map<std::string, Kind> s_kinds = {
        {"bvadd", Kind::BV_ADD},
        {"bvsub", Kind::BV_SUB},
        {"bvmul", Kind::BV_MUL},
        {"bvneg", Kind::BV_NEG},
        {"bvnot", Kind::BV_NOT},
        {"bvand", Kind::BV_AND},
        {"bvor", Kind::BV_OR},
        {"bvxor", Kind::BV_XOR},
        {"bvxnor", Kind::BV_XNOR},
        {"bvnand", Kind::BV_NAND},
        {"bvnor", Kind::BV_NOR},
        {"bvshl", Kind::BV_SHL},
        {"bvlshr", Kind::BV_SHR},
        {"bvashr", Kind::BV_ASHR},
        {"bvult", Kind::BV_ULT},
        {"bvule", Kind::BV_ULE},
        {"bvugt", Kind::BV_UGT},
        {"bvuge", Kind::BV_UGE},
        {"bvslt", Kind::BV_SLT},
        {"bvsle", Kind::BV_SLE},
        {"bvsgt", Kind::BV_SGT},
        {"bvsge", Kind::BV_SGE},
        {"bvsaddo", Kind::BV_SADDO},
        {"bvuaddo", Kind::BV_UADDO},
        {"bvssubo", Kind::BV_SSUBO},
        {"bvnego", Kind::BV_NEGO},
        {"not", Kind::NOT},
        {"and", Kind::AND},
        {"or", Kind::OR},
        {"xor", Kind::XOR},
        {"=", Kind::EQUAL},
        {"distinct", Kind::DISTINCT},
        {"ite", Kind::ITE},
    };
    if (e.children.empty())
    {
      if (e.atom == "true" || e.atom == "false")
      {
        ground = true;
        return d_nm.mk_value(e.atom == "true");
      }
      ground = false;
      return inst.vars.at(e.atom);
    }
    const std::string& op = e.children[0].atom;
    if (op == "@bv")
    {
      ground = true;
      return d_nm.mk_value(
          BitVector::from_si(inst.size, eval_int(e.children[1], inst), true));
    }
    Kind kind = s_kinds.at(op);
    std::vector<Node> args;
    ground = true;
    for (size_t i = 1; i < e.children.size(); ++i)
    {
      bool g;
      args.push_back(mk_term(e.children[i], inst, eval, mirror, g));
      ground = ground && g;
    }
    if (mirror && KindInfo::is_commutative(kind))
    {
      std::reverse(args.begin(), args.end());
    }
    Node res;
    if (args.size() > 2 && kind != Kind::DISTINCT)
    {
      assert(KindInfo::is_left_associative(kind));
      res = d_nm.mk_node(kind, {args[0], args[1]});
      for (size_t i = 2; i < args.size(); ++i)
      {
        res = d_nm.mk_node(kind, {res, args[i]});
      }
    }
    else
    {
      res = d_nm.mk_node(kind, args);
    }
    if (ground && eval)
    {
      res = d_rewriter.eval(res);
    }
    return res;
  }

  Node mk_term(const char* str, const Instance& inst, bool eval, bool mirror)
  {
    bool ground;
    return mk_term(parse_sexpr(str), inst, eval, mirror, ground);
  }

  /**
   * Check if the given nodes are equal up to the order of the children of
   * commutative operators.
   */
  static bool equal_up_to_commutativity(const Node& a, const Node& b)
  {
    if (a == b)
    {
      return true;
    }
    if (a.kind() != b.kind() || a.num_children() != b.num_children()
        || a.num_children() == 0 || a.num_indices() != b.num_indices())
    {
      return false;
    }
    for (size_t i = 0; i < a.num_indices(); ++i)
    {
      if (a.index(i) != b.index(i))
      {
        return false;
      }
    }
    bool equal = true;
    for (size_t i = 0; i < a.num_children() && equal; ++i)
    {
      equal = equal_up_to_commutativity(a[i], b[i]);
    }
    return equal
           || (a.num_children() == 2 && KindInfo::is_commutative(a.kind())
               && equal_up_to_commutativity(a[0], b[1])
               && equal_up_to_commutativity(a[1], b[0]));
  }

  /**
   * Check if the given nodes evaluate to the same value under (exhaustively
   * enumerated or random) assignments to the variables of the instance.
   */
  bool equivalent(const Instance& inst,
                  const Node& a,
                  const Node& b,
                  std::mt19937_64& rng,
                  std::string& model)
  {
    std::vector<Node> vars;
    uint64_t num_bits = 0;
    for (const auto& [name, var] : inst.vars)
    {
      vars.push_back(var);
      num_bits += var.type().is_bool() ? 1 : var.type().bv_size();
    }
    std::sort(vars.begin(), vars.end(), [](const Node& x, const Node& y) {
      return x.id() < y.id();
    });
    bool exhaustive    = num_bits <= 12;
    uint64_t num_tests = exhaustive ? (uint64_t{1} << num_bits) : 64;
    for (uint64_t t = 0; t < num_tests; ++t)
    {
      std::unordered_map<Node, Node> subst;
      uint64_t bits = t;
      for (const Node& var : vars)
      {
        if (var.type().is_bool())
        {
          bool val = exhaustive ? (bits & 1) : (rng() & 1);
          bits >>= 1;
          subst.emplace(var, d_nm.mk_value(val));
        }
        else
        {
          uint64_t size = var.type().bv_size();
          BitVector val = BitVector::mk_zero(size);
          if (exhaustive)
          {
            val = BitVector::from_ui(size, bits & ((uint64_t{1} << size) - 1));
            bits >>= size;
          }
          else
          {
            // Mix special values and random values.
            switch (rng() % 8)
            {
              case 0: val = BitVector::mk_zero(size); break;
              case 1: val = BitVector::mk_one(size); break;
              case 2: val = BitVector::mk_ones(size); break;
              case 3: val = BitVector::mk_min_signed(size); break;
              case 4: val = BitVector::mk_max_signed(size); break;
              default:
                for (uint64_t i = 0; i < size; ++i)
                {
                  val.set_bit(i, rng() & 1);
                }
            }
          }
          subst.emplace(var, d_nm.mk_value(val));
        }
      }
      std::unordered_map<Node, Node> cache;
      Node va = d_rewriter.eval(utils::substitute(d_nm, a, subst, cache));
      Node vb = d_rewriter.eval(utils::substitute(d_nm, b, subst, cache));
      if (va != vb)
      {
        std::stringstream ss;
        for (const Node& var : vars)
        {
          ss << " " << var << " = " << subst.at(var);
        }
        model = ss.str();
        return false;
      }
    }
    return true;
  }
};

TEST_F(TestRewriterRare, option_disabled_by_default)
{
  ASSERT_FALSE(option::Options().rare_rules());
}

TEST_F(TestRewriterRare, option_gating)
{
  // (bvadd (bvadd x0 x1) (bvadd (bvnot x0) 1)) is only rewritten (to x1) if
  // RARE rules are enabled and the rewrite level is at least 1.
  Type bv8 = d_nm.mk_bv_type(8);
  Node x0  = d_nm.mk_const(bv8, "x0");
  Node x1  = d_nm.mk_const(bv8, "x1");
  Node one = d_nm.mk_value(BitVector::mk_one(8));
  Node lhs = d_nm.mk_node(
      Kind::BV_ADD,
      {d_nm.mk_node(Kind::BV_ADD, {x0, x1}),
       d_nm.mk_node(Kind::BV_ADD, {d_nm.mk_node(Kind::BV_NOT, {x0}), one})});
  for (uint64_t level = 0; level <= Rewriter::LEVEL_MAX; ++level)
  {
    option::Options off, on;
    off.rewrite_level.set(level);
    on.rewrite_level.set(level);
    on.rare_rules.set(true);
    Env env_off(d_nm, d_sat_factory, off);
    Env env_on(d_nm, d_sat_factory, on);
    Node res_off = env_off.rewriter().rewrite(lhs);
    Node res_on  = env_on.rewriter().rewrite(lhs);
    ASSERT_NE(res_off, x1);
    if (level == 0)
    {
      ASSERT_EQ(res_on, res_off);
    }
    else
    {
      ASSERT_EQ(res_on, x1);
    }
  }
}

TEST_F(TestRewriterRare, rules)
{
  option::Options options;
  options.rare_rules.set(true);
  Env env(d_nm, d_sat_factory, options);
  Rewriter& rewriter = env.rewriter();
  std::mt19937_64 rng(42);

  ASSERT_EQ(s_rules.size(), static_cast<size_t>(RareRuleKind::NUM_RULES));
  for (size_t i = 0; i < s_rules.size(); ++i)
  {
    const Rule& rule = s_rules[i];
    ASSERT_EQ(static_cast<size_t>(rule.kind), i);
    for (uint64_t size : {1, 2, 3, 8, 65})
    {
      for (bool mirror : {false, true})
      {
        std::stringstream id;
        id << size << (mirror ? "m" : "");
        Instance inst = mk_instance(rule, size, id.str());
        // The match pattern in normal form, i.e., with evaluated ground terms.
        Node lhs = mk_term(rule.lhs, inst, true, mirror);
        // The rewritten term as specified, without rewriting.
        Node rhs = mk_term(rule.rhs, inst, false, false);
        std::string model;
        bool valid = equivalent(inst, lhs, rhs, rng, model);
        if (rule.guard == Guard::INVALID && size == 1)
        {
          // These rules are not valid at bit-width 1 (and must not apply).
          ASSERT_FALSE(valid) << rule.kind << " is valid for bit-width 1";
        }
        else
        {
          ASSERT_TRUE(valid) << rule.kind << " is not valid for bit-width "
                             << size << ":" << model;
        }

        RareMatch match;
        bool matched = rare_match(rule.kind, lhs, match);
        ASSERT_EQ(matched, rule.guard == Guard::NONE || size > 1)
            << rule.kind << " on " << lhs;
        if (matched)
        {
          ASSERT_EQ(match.kind, rule.kind);
          Node res = rare_build(rewriter, match);
          ASSERT_TRUE(equivalent(inst, lhs, res, rng, model))
              << rule.kind << ": " << lhs << " -> " << res << ":" << model;
        }
        Node full = rewriter.rewrite(lhs);
        ASSERT_TRUE(equivalent(inst, lhs, full, rng, model))
            << rule.kind << ": " << lhs << " -> " << full << ":" << model;
      }
    }
  }
}

TEST_F(TestRewriterRare, rules_effective)
{
  // The built-in rewrite rules must not rewrite the result of a rule back to
  // its match pattern, else the rule never applies.
  std::vector<std::string> noops;
  for (const Rule& rule : s_rules)
  {
    bool noop = true;
    for (uint64_t size : {2, 8, 32, 65})
    {
      Instance inst = mk_instance(rule, size, "e" + std::to_string(size));
      Node lhs      = mk_term(rule.lhs, inst, true, false);
      Node rhs      = mk_term(rule.rhs, inst, false, false);
      if (d_rewriter.rewrite(lhs) != d_rewriter.rewrite(rhs))
      {
        noop = false;
        break;
      }
    }
    if (noop)
    {
      std::stringstream ss;
      ss << rule.kind;
      noops.push_back(ss.str());
    }
  }
  std::stringstream ss;
  for (const std::string& name : noops)
  {
    ss << " " << name;
  }
  ASSERT_TRUE(noops.empty()) << "rules without effect:" << ss.str();
}

TEST_F(TestRewriterRare, rules_normal_form)
{
  // The result of a rule must be in normal form w.r.t. the built-in rewrite
  // rules (up to the order of the children of commutative operators), else
  // rewriting the result may lead back to the match pattern of the rule
  // (rewrite cycle).
  std::vector<std::string> failed;
  for (const Rule& rule : s_rules)
  {
    for (uint64_t size : {1, 2, 3, 4, 8, 13, 32, 64, 65})
    {
      Instance inst = mk_instance(rule, size, "n" + std::to_string(size));
      Node rhs      = mk_term(rule.rhs, inst, true, false);
      bool normal   = equal_up_to_commutativity(d_rewriter.rewrite(rhs), rhs);
      if (rule.guard != Guard::NONE && size == 1)
      {
        if (rule.guard == Guard::NOT_NORMAL)
        {
          // The guard is required, and the rule would not apply at
          // bit-width 1 anyway since its match pattern is not in normal form.
          Node lhs = mk_term(rule.lhs, inst, true, false);
          ASSERT_FALSE(normal) << rule.kind;
          ASSERT_FALSE(equal_up_to_commutativity(d_rewriter.rewrite(lhs), lhs))
              << rule.kind;
        }
        continue;
      }
      if (!normal)
      {
        std::stringstream ss;
        ss << rule.kind << "@" << size;
        failed.push_back(ss.str());
      }
    }
  }
  std::stringstream ss;
  for (const std::string& name : failed)
  {
    ss << " " << name;
  }
  ASSERT_TRUE(failed.empty()) << "results not in normal form:" << ss.str();
}

// clang-format off
const std::vector<TestRewriterRare::Rule> TestRewriterRare::s_rules = {
    {RareRuleKind::ADDITIVE_CANCEL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) x1) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::ADD_ALL_ONES_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))) x2)"},
    {RareRuleKind::ADD_COMPLEMENTED_NEGATION, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0))))",
     "x1"},
    {RareRuleKind::ADD_COMPLEMENT_CANCEL, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvnot x1)) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "x0"},
    {RareRuleKind::ADD_NEGATED_ZERO_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::ADD_NOT_SUM_CANCEL, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd x0 (bvnot (bvadd x0 x1)))",
     "(bvnot x1)"},
    {RareRuleKind::ADD_NOT_SUM_WITH_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvadd (bvnot x0) (bvnot x1)) (bvadd x2 (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::ADD_ONE_VIA_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvadd x0 x1) (bvadd x2 x3)) (@bv 1 (@bvsize x0))) x4)",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x2 x3 x4)"},
    {RareRuleKind::ADD_ONE_VIA_COMPLEMENTED_SUM_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvxor x0 (bvxor x1 x2)) (bvadd x3 (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd (bvnot x3) (bvnot (bvxor x0 (bvxor x1 x2)))))"},
    {RareRuleKind::ASHR_ADD_ONE_NONTRIVIAL, Guard::INVALID,
     "((x0 ?BitVec))",
     "(not (= (@bv 0 (@bvsize x0)) (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))",
     "(and (not (= x0 (@bv 0 (@bvsize x0)))) (not (= x0 (bvnot (@bv 0 (@bvsize x0))))))"},
    {RareRuleKind::ASHR_COMPLEMENT_ADD_ROUNDING, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvnot (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0))))",
     "(bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_COMPLEMENT_NEGATED_INPUT, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::ASHR_HALF_SUM_FOLD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::ASHR_NEGATED_INCREMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvadd (bvadd x0 (bvashr (bvnot x0) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvand x0 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::ASHR_NEGATED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_NEGATED_SUM_SPLIT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x2 (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_PLUS_LOW_BIT, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvand x0 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::ASHR_SIMPLIFY_ADD_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_SUBTRACT_ONE_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_SUM_AFTER_CANCELLED_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2) (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_SUM_CANCEL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_SUM_MINUS_ONE_HALF, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::ASHR_SUM_OFFSET_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::AVERAGE_FLOOR_SIGNED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))) (bvadd x0 x1))",
     "(bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) (bvand (bvadd x0 x1) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_ALLONES_EQUALITY_REVERSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (p0 Bool) (x1 ?BitVec) (x2 ?BitVec))",
     "(and (and (= (@bv 0 (@bvsize x0)) x0) p0) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))",
     "(and p0 (and (= x0 (@bv 0 (@bvsize x0))) (= (bvadd x2 (@bv 1 (@bvsize x0))) x1)))"},
    {RareRuleKind::BVADD_ALL_ONES_AS_MINUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2)"},
    {RareRuleKind::BVADD_ALL_ONES_CANCEL_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvnot x2)))",
     "(bvadd x0 x1 (bvnot x2))"},
    {RareRuleKind::BVADD_ALL_ONES_EQUALS_XOR, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvxor x1 x2)))",
     "(= (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2))"},
    {RareRuleKind::BVADD_CANCEL_ALLONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) x1))",
     "(bvadd x1 (bvnot x0))"},
    {RareRuleKind::BVADD_CANCEL_ALLONES_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)"},
    {RareRuleKind::BVADD_CANCEL_ALLONES_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd x0 (bvadd (bvnot x1) x2))"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot (bvadd x1 x2)) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))) (bvadd x0 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 x3)))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 x1) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_AND_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd (@bv 1 (@bvsize x0)) (bvadd x2 x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_ALL_ONES_WITH_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))) x3)",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENTED_SUMMAND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd x1 (bvadd x2 (bvnot (bvadd x0 x3)))))",
     "(bvadd x1 (bvadd x2 (bvnot x3)))"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvadd x1 (@bv 1 (@bvsize x0))) (bvadd x2 x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) (bvadd x0 x2))",
     "(bvnot (bvadd (bvnot x2) x1))"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd x1 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) (bvadd x3 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2)) (bvadd x3 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 x1) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_COMPLEMENT_OFFSET_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd x1 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3)) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_AND_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 x2)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_MINUS_ONE_PLUS_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))"},
    {RareRuleKind::BVADD_CANCEL_NEGATED_ZERO, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVADD_CANCEL_NEGATIVE_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_NEGATIVE_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0)))) x2) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))"},
    {RareRuleKind::BVADD_CANCEL_NEG_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_NEG_ONE_AND_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2))) x3)",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_CANCEL_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_CANCEL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::BVADD_CANCEL_ONE_MINUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CANCEL_ONE_MINUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_CARRY_CONSTANT_FOLD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (bvnot x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvnot x1) x2)"},
    {RareRuleKind::BVADD_COLLAPSE_ALL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvnot x1))"},
    {RareRuleKind::BVADD_COMBINE_COMPLEMENTED_PAIR, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd x1 (bvadd x2 x3))) (bvadd x4 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x2 x3 x4)"},
    {RareRuleKind::BVADD_COMPLEMENTED_NEGATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVADD_COMPLEMENT_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd x1 (bvnot x0))"},
    {RareRuleKind::BVADD_COMPLEMENT_EQUALITY_XOR, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2))",
     "(= (bvnot (bvxor x0 x2)) (bvadd x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_COMPLEMENT_REASSOCIATE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (bvnot x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x1 (bvnot (bvadd x0 x2)))"},
    {RareRuleKind::BVADD_COMPLEMENT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))",
     "(bvadd x2 (bvnot (bvadd x0 x1)))"},
    {RareRuleKind::BVADD_COMPLEMENT_SUM_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot x1) (bvnot x2)) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::BVADD_FOLD_MINUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvashr x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_FOLD_NEGATED_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2)",
     "(bvadd x0 (bvadd (bvnot x1) x2))"},
    {RareRuleKind::BVADD_INVERSE_REARRANGE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvadd (bvadd x1 (bvnot x2)) x2))",
     "(= (bvadd x0 (@bv 1 (@bvsize x0))) x1)"},
    {RareRuleKind::BVADD_MINUS_ONE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_MINUS_ONE_EQUALITY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)",
     "(= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(= x0 (bvadd x1 x2))"},
    {RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) x1) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvashr x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_MINUS_ONE_PLUS_ONE_5, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvand (bvxor x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))) x3)",
     "(bvand (bvxor x0 (bvadd x1 x2)) x3)"},
    {RareRuleKind::BVADD_MINUS_ONE_SUBTRACTION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))) x2)",
     "(= (bvadd x0 (bvnot x1)) x2)"},
    {RareRuleKind::BVADD_NEGATED_SHIFT_CANCELLATION, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))) (bvashr x1 (@bv 1 (@bvsize x0))))",
     "x0"},
    {RareRuleKind::BVADD_NEGATED_X1_AND_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvnot x1))"},
    {RareRuleKind::BVADD_NEGATED_ZERO_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_NEGATED_ZERO_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 x1) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) (bvadd x3 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_NEG_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)))",
     "(bvadd x0 (bvadd x0 x1))"},
    {RareRuleKind::BVADD_NEG_ONE_AND_ONE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2)"},
    {RareRuleKind::BVADD_NEG_ONE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvashr x1 (@bv 1 (@bvsize x0)))) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2)"},
    {RareRuleKind::BVADD_NEG_ONE_CANCEL_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_NEG_ONE_CANCEL_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) x2)",
     "(bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))"},
    {RareRuleKind::BVADD_NEG_ONE_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1)"},
    {RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvxor x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvxor x0 (bvadd x1 x2))"},
    {RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCELLATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::BVADD_NEG_ONE_PLUS_ONE_CANCEL_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) x1) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)"},
    {RareRuleKind::BVADD_NOT_AND_TO_NOT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot x0) (bvadd (@bv 1 (@bvsize x0)) (bvand (bvand x1 x2) x3)))",
     "(bvnot (bvadd x0 (bvnot (bvand (bvand x1 x2) x3))))"},
    {RareRuleKind::BVADD_NOT_COMPLEMENT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvnot x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::BVADD_NOT_SUBTRACT_SIMPLIFICATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) x0)) (@bv 1 (@bvsize x0))) x1) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvadd x1 (bvnot x0)) (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::BVADD_NOT_SUB_CONSTANT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvnot x1)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x1 (bvadd (bvnot x0) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::BVADD_NOT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) (bvnot x2))",
     "(bvnot (bvadd (bvadd x0 x1) x2))"},
    {RareRuleKind::BVADD_NOT_SUM_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::BVADD_NOT_ZERO_COLLAPSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd (bvadd x1 x2) (bvnot x0))"},
    {RareRuleKind::BVADD_ONES_AND_INCREMENT_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))))",
     "(bvadd x0 (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVADD_ONE_AS_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvxor (bvadd x0 x1) (bvadd x2 x3)) (bvadd x4 (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd (bvnot (bvxor (bvadd x0 x1) (bvadd x2 x3))) (bvnot x4)))"},
    {RareRuleKind::BVADD_ONE_AS_COMPLEMENT_NEGATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3))))",
     "(bvnot (bvadd (bvnot x0) (bvnot (bvadd x1 (bvadd x2 x3)))))"},
    {RareRuleKind::BVADD_ONE_AS_NEGATED_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvashr (bvadd x2 x3) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) (bvashr (bvadd x2 x3) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVADD_ONE_COMPLEMENT_MINUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BVADD_ONE_EQUALS_BITWISE_DIFFERENCE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvxor (bvand x1 x2) x1)))",
     "(= (bvadd x0 (@bv 1 (@bvsize x0))) (bvand x1 (bvnot x2)))"},
    {RareRuleKind::BVADD_REASSOCIATE_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x0 (bvadd x2 x3)))",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) x0 x2 x3)"},
    {RareRuleKind::BVADD_REASSOCIATE_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvand x1 x2) x3))",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x3))) (bvand x1 x2))"},
    {RareRuleKind::BVADD_SUB_CANCELLATION, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x1)",
     "x0"},
    {RareRuleKind::BVAND_CLEAR_BITS, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvand x0 (bvand (bvnot (bvand x0 x1)) (bvnot x2)))",
     "(bvand x0 (bvnot x1) (bvnot x2))"},
    {RareRuleKind::BVAND_DISTRIBUTE_INVERTED_FACTOR, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvand x0 (bvand (bvnot (bvand (bvand x0 x1) x2)) x3))",
     "(bvand x0 (bvand x3 (bvnot (bvand x1 x2))))"},
    {RareRuleKind::BVAND_EQUALITY_IDEMPOTENCE, Guard::NONE,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(and (and p0 (= (bvand x0 x1) x2)) (= x0 x2))",
     "(and p0 (= x0 x2) (= (bvand x0 (bvnot x1)) (@bv 0 (@bvsize x0))))"},
    {RareRuleKind::BVAND_MASK_DISTRIBUTION, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvand (bvand x0 (bvnot (bvand x1 (bvnot x2)))) x1)",
     "(bvand x0 x1 x2)"},
    {RareRuleKind::BVASHR_CANCEL_ADDITIVE_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::BVASHR_NEGATED_DIFFERENCE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvnot (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x1 (bvnot x0)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::BVNOT_ADD_CANCEL_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))"},
    {RareRuleKind::BVNOT_ADD_COMPLEMENT, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))))",
     "(bvnot x1)"},
    {RareRuleKind::BVNOT_ADD_COMPLEMENTED_AND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvnot (bvand x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvand x0 x1) (bvnot x2))"},
    {RareRuleKind::BVNOT_ADD_IDENTITY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot x0) (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVNOT_ADD_INVERSE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd x1 (bvnot (bvadd x0 x2)))))",
     "(bvnot (bvadd x1 (bvnot x2)))"},
    {RareRuleKind::BVNOT_ADD_MASK_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvand x1 (@bv 1 (@bvsize x0)))))))",
     "(bvadd (bvnot x0) (bvand x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVNOT_ADD_NEGATED_SUBTRAHEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))",
     "(bvadd x1 (bvnot x0))"},
    {RareRuleKind::BVNOT_ADD_NEGATED_SUBTRAHEND_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvnot x1))"},
    {RareRuleKind::BVNOT_ADD_NEGATED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))) x2))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::BVNOT_ADD_NEGATION_COLLAPSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvnot x0) (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvnot (bvand x1 x2)))"},
    {RareRuleKind::BVNOT_ADD_NORMALIZE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::BVNOT_ADD_ONE_AND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) (bvnot (bvand x1 x2)))"},
    {RareRuleKind::BVNOT_ADD_ONE_COLLAPSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd x0 (bvadd (bvand x1 x2) (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 (bvand x1 x2)))"},
    {RareRuleKind::BVNOT_ADD_ONE_SIMPLIFY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) (bvadd x2 x3))",
     "(bvadd (bvnot x0) (bvnot x1) x2 x3)"},
    {RareRuleKind::BVNOT_ADD_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) (bvnot x1))"},
    {RareRuleKind::BVNOT_ADD_SPLIT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) (bvnot (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVNOT_ADD_SUCCESSOR, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2))) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::BVNOT_ADD_SUM_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) (bvnot (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVNOT_ADD_TO_COMPLEMENT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot (bvashr x0 (@bv 1 (@bvsize x0)))) (bvnot x1))"},
    {RareRuleKind::BVNOT_ADD_XOR, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2)))",
     "(bvadd (bvnot x0) (bvnot (bvxor x1 x2)))"},
    {RareRuleKind::BVNOT_ADD_ZERO_MINUS_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::BVNOT_ALLONES_ADD_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2))",
     "(not (= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVNOT_INCREMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd x2 (bvadd (bvnot x0) (bvnot x1)))"},
    {RareRuleKind::BVNOT_MINUS_ONE_ADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))"},
    {RareRuleKind::BVNOT_SUM_COLLAPSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvnot (bvadd x0 x1))"},
    {RareRuleKind::BVNOT_SUM_COMPLEMENTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)))",
     "(bvadd x0 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::BVNOT_SUM_DIFFERENCE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2))",
     "(bvadd (bvnot (bvadd x0 x2)) x1)"},
    {RareRuleKind::BVNOT_SUM_DISTRIBUTE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))) x3))",
     "(bvadd x0 x3 (bvnot x1) (bvnot x2))"},
    {RareRuleKind::BVNOT_SUM_GROUPED_NEGATIONS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x2 x3)))",
     "(bvadd (bvnot (bvadd x0 x1)) (bvnot (bvadd x2 x3)))"},
    {RareRuleKind::BVNOT_SUM_WITH_INCREMENTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) (bvnot x1) (bvnot x2))"},
    {RareRuleKind::BVNOT_SUM_WITH_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)))",
     "(bvnot (bvadd (bvadd x0 x1) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvashr x1 (@bv 1 (@bvsize x0)))) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))"},
    {RareRuleKind::BVNOT_ZERO_ADD_EQUALITY, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and (and p0 p1) (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))",
     "(and (and p0 p1) (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_IDENTITY, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and p0 (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))",
     "(and p0 (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_IDENTITY_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (p0 Bool) (x2 ?BitVec))",
     "(and (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1) (and p0 (= (bvnot (@bv 0 (@bvsize x0))) x2)))",
     "(and p0 (and (= (bvadd x1 (@bv 1 (@bvsize x0))) x0) (= x2 (bvnot (@bv 0 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_INCREMENT, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and (and p0 p1) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))",
     "(and p0 (and p1 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0)))"},
    {RareRuleKind::BVNOT_ZERO_ADD_INVERSE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))",
     "(not (= (bvadd x1 (@bv 1 (@bvsize x0))) x0))"},
    {RareRuleKind::BVNOT_ZERO_ADD_INVERT, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))",
     "(and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) (not p1))",
     "(and p0 (and (not p1) (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_ONE_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvashr x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_ONE_REASSOCIATE, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(and p0 (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2)))",
     "(and p0 (not (= (bvadd x0 x1) (bvadd x2 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_ADD_REVERSE, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and p0 (not (and p1 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))))",
     "(and p0 (not (and p1 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0))))"},
    {RareRuleKind::BVNOT_ZERO_PLUS_INCREMENT_INVERSE, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))",
     "(and p0 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BVNOT_ZERO_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALITY, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(not (and (and p0 p1) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))",
     "(not (and p0 p1 (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALITY_2, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))",
     "(and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) p1)",
     "(and p0 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))) p1)"},
    {RareRuleKind::BVNOT_ZERO_PLUS_X_EQUALS_SUCCESSOR, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool) (p2 Bool))",
     "(and (and (and p0 (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) p1) p2)",
     "(and p0 (and p1 (and p2 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))))"},
    {RareRuleKind::BV_ADD_ALL_ONES_CANCEL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2)) x3))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::BV_ADD_MINUS_ONE_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2)) x0)",
     "(bvxor (bvadd x0 (bvadd x1 x2)) x0)"},
    {RareRuleKind::BV_COMPLEMENT_PLUS_X_TO_INCREMENT, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (p2 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and (and (and p0 p1) p2) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))",
     "(and p0 p1 p2 (= x0 (bvadd x1 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::BV_NEGATED_SUM_EXPRESSION, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and p0 (bvslt (@bv 0 (@bvsize x0)) (bvadd x0 (bvnot (bvadd x0 x1)))))",
     "(and p0 (bvslt (@bv 0 (@bvsize x0)) (bvnot x1)))"},
    {RareRuleKind::BV_SUB_INCREMENT_EQUIVALENCE, Guard::NOT_NORMAL,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and (not p0) (not (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))",
     "(and (not p0) (not (= x0 (bvadd x1 (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::BV_SUB_VIA_NEGATED_OPERANDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd x1 (bvnot x0)))"},
    {RareRuleKind::CANCELLED_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd x1 (bvnot (bvadd x0 x2))))",
     "(bvadd x1 (bvnot x2))"},
    {RareRuleKind::CANCEL_ADDITIVE_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))",
     "(bvnot (bvadd x1 (bvnot x2)))"},
    {RareRuleKind::CANCEL_ADDITIVE_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::CANCEL_ADDITIVE_CONSTANTS_BEFORE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::CANCEL_ADDITIVE_INVERSES_SIGNED_LT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvslt (bvadd (bvadd x0 (bvnot x1)) (bvadd x1 (@bv 1 (@bvsize x0)))) x2)",
     "(bvslt x0 x2)"},
    {RareRuleKind::CANCEL_ADDITIVE_NEGATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))) x2))",
     "(bvadd x0 x1)"},
    {RareRuleKind::CANCEL_ADDITIVE_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::CANCEL_ADD_AND_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvnot (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvnot (bvadd x1 (bvnot x2)))"},
    {RareRuleKind::CANCEL_ADD_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(= x0 (bvadd (bvadd x1 x2) (bvadd x3 (bvnot (bvadd x1 x2)))))",
     "(= (bvadd x0 (@bv 1 (@bvsize x0))) x3)"},
    {RareRuleKind::CANCEL_ADD_INVERSE, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x1))",
     "(bvnot x0)"},
    {RareRuleKind::CANCEL_ADD_ONE_AND_ALL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 x3))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_ADD_ONE_FROM_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvnot (bvadd x0 x1)) x2)"},
    {RareRuleKind::CANCEL_ALL_ONES_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0))) x2))",
     "(bvadd x0 (bvnot x1) x2)"},
    {RareRuleKind::CANCEL_ALL_ONES_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::CANCEL_ALL_ONES_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_ALL_ONES_AND_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::CANCEL_ALL_ONES_AND_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::CANCEL_ALL_ONES_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::CANCEL_ALL_ONES_OFFSET_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2)) x3)",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_ALL_ONES_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0)))) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2))"},
    {RareRuleKind::CANCEL_ALL_ONES_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2)) x3) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_BV_NEGATED_ZERO_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2))) x3)",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_COMPLEMENTED_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvadd x0 x1) (bvadd (bvnot x1) (@bv 2 (@bvsize x0))))"},
    {RareRuleKind::CANCEL_COMPLEMENTED_SUM, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd x2 (bvnot (bvadd x0 x1))))",
     "x2"},
    {RareRuleKind::CANCEL_COMPLEMENTED_ZERO_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_COMPLEMENT_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(not (= x0 (bvadd (bvadd x1 (bvnot x2)) x2)))",
     "(not (= (bvadd x0 (@bv 1 (@bvsize x0))) x1))"},
    {RareRuleKind::CANCEL_COMPLEMENT_INCREMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 x1) (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))) x2)",
     "(bvadd x1 x2)"},
    {RareRuleKind::CANCEL_MINUS_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1))"},
    {RareRuleKind::CANCEL_MINUS_ONE_AND_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1)"},
    {RareRuleKind::CANCEL_MINUS_ONE_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2) x3))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_MINUS_ONE_OFFSET_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 (bvadd x2 x3))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2)"},
    {RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3)))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_MINUS_ONE_PLUS_ONE_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 x2))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::CANCEL_MODULAR_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1)) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1) x2)"},
    {RareRuleKind::CANCEL_NEGATED_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))",
     "(bvadd x1 (bvnot (bvashr x0 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::CANCEL_NEGATED_ADDEND_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd x1 (bvadd (bvnot x0) (@bv 1 (@bvsize x0)))) x2))",
     "(bvadd x1 x2)"},
    {RareRuleKind::CANCEL_NEGATED_X0, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot x0) (@bv 1 (@bvsize x0))) (bvadd x1 (bvadd x0 x2)))",
     "(bvadd x1 x2)"},
    {RareRuleKind::CANCEL_NEGATED_ZERO_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) x3)",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_NEGATIVE_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd x1 (bvashr x0 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::CANCEL_NEGATIVE_ONE_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1))",
     "(bvadd x0 x1)"},
    {RareRuleKind::CANCEL_NESTED_ADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd x1 (bvadd x2 (bvnot (bvadd x1 x3)))))",
     "(bvadd x0 x2 (bvnot x3))"},
    {RareRuleKind::CANCEL_NOT_ZERO_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) x3) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::CANCEL_ONE_MINUS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::CANCEL_ONE_PLUS_ALL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::CANCEL_SHIFTED_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd x1 (bvnot (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x2))))",
     "(bvadd x1 (bvnot x2))"},
    {RareRuleKind::CANCEL_SHIFT_AND_COMPLEMENT, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1) (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0))))))",
     "x1"},
    {RareRuleKind::CANCEL_XOR_COMPLEMENT_OFFSET, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd x1 (bvnot x0)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x1 x2)"},
    {RareRuleKind::CARRY_INCREMENT_ADD_COMPLEMENTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvnot (bvadd (bvnot x0) (bvnot x1))) (bvnot (bvadd (bvnot x2) (bvnot x3))))"},
    {RareRuleKind::COLLAPSE_ADDITIVE_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COLLAPSE_ADDITIVE_CONSTANTS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (bvnot x2))"},
    {RareRuleKind::COLLAPSE_ALL_ONES_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 (bvnot x1)) (bvnot x2)))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvadd x1 (@bv 1 (@bvsize x0)))) x2)",
     "(bvadd x1 (bvnot x0) x2)"},
    {RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2)) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x2 (bvnot x1))"},
    {RareRuleKind::COLLAPSE_COMPLEMENTED_ADDENDS_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvadd x1 x2) (bvnot x0))"},
    {RareRuleKind::COLLAPSE_COMPLEMENTED_ZERO_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COLLAPSE_COMPLEMENT_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd x1 (bvadd x2 (bvadd x3 (@bv 1 (@bvsize x0)))))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::COLLAPSE_COMPLEMENT_SUBTRACTION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2))",
     "(bvadd x0 (bvnot x1) x2)"},
    {RareRuleKind::COLLAPSE_MINUS_ONE_ADDENDS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x1 (@bv 1 (@bvsize x0))))) x2)",
     "(bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0))) x2 (@bv (- 0 2) (@bvsize x0)))"},
    {RareRuleKind::COLLAPSE_MINUS_ONE_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd x1 (bvashr (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::COLLAPSE_NOT_ZERO_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2)"},
    {RareRuleKind::COLLAPSE_ONES_COMPLEMENT_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDED_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvadd x0 x1) (bvadd x2 (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::COMBINE_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 x1) (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x2) x3)))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::COMBINE_ADDENDS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))) x2) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDENDS_AND_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDENDS_AND_CONSTANTS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (bvashr x2 (@bv 1 (@bvsize x0))) (@bv (- 2) (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDENDS_BEFORE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 (@bv 3 (@bvsize x0))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDENDS_BEFORE_ARITHMETIC_SHIFT_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd (bvadd x0 x1) x0) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDITIVE_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd x1 (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ADDITIVE_CONSTANTS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_ALL_ONES_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))) (bvnot (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::COMBINE_BVADD_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_CANCELING_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvadd x0 x1))"},
    {RareRuleKind::COMBINE_COMPLEMENTED_ADDENDS_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvnot (@bv 0 (@bvsize x0))) x1))",
     "(bvnot (bvadd (bvnot x0) (bvnot x1) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::COMBINE_COMPLEMENTED_ADDENDS_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0))) (bvnot x2))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::COMBINE_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) x2)",
     "(bvadd (bvnot (bvadd x0 x1)) x2)"},
    {RareRuleKind::COMBINE_CONSTANT_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x1 (@bv 1 (@bvsize x0))) (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_DUPLICATE_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd (bvadd x2 (@bv 1 (@bvsize x0))) (bvadd x0 x1)))",
     "(bvadd (bvadd x0 x1) (bvadd (bvadd x0 x1) x2))"},
    {RareRuleKind::COMBINE_INCREMENT_AND_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x1)) x2))",
     "(bvadd x0 x2 (bvnot x1))"},
    {RareRuleKind::COMBINE_NESTED_ADDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::COMBINE_OFFSET_ADDITIONS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::COMPLEMENTED_INCREMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 x1))"},
    {RareRuleKind::COMPLEMENTED_INCREMENTED_SUM_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvnot (bvadd x0 (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 x1))"},
    {RareRuleKind::COMPLEMENTED_SUM_NEGATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd x0 x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::COMPLEMENTED_SUM_TO_OFFSET_SUBTRACTION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) x1)) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvadd (bvnot x1) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::CONTRADICTORY_BOOLEAN_CONJUNCTION, Guard::NONE,
     "((p0 Bool) (x0 ?BitVec) (p1 Bool))",
     "(and (not p0) (and (= (@bv 0 (@bvsize x0)) x0) (and p0 p1)))",
     "false"},
    {RareRuleKind::CONTRADICTORY_BOOLEAN_CONJUNCTION_2, Guard::NONE,
     "((p0 Bool) (x0 ?BitVec) (p1 Bool))",
     "(and (not p0) (and (and (= (@bv 0 (@bvsize x0)) x0) p0) p1))",
     "false"},
    {RareRuleKind::CONTRADICTORY_EQUALITY, Guard::NONE,
     "((p0 Bool) (x0 ?BitVec) (x1 ?BitVec) (p1 Bool))",
     "(and (and (and p0 (not (= x0 x1))) p1) (= x0 x1))",
     "false"},
    {RareRuleKind::CONTRADICTORY_ZERO_TEST, Guard::NONE,
     "((x0 ?BitVec) (p0 Bool) (p1 Bool))",
     "(and (not (= (@bv 0 (@bvsize x0)) x0)) (and (and (= (@bv 0 (@bvsize x0)) x0) p0) p1))",
     "false"},
    {RareRuleKind::DOUBLE_BITWISE_NEGATION_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1)"},
    {RareRuleKind::DOUBLE_NEGATED_SUM_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0))) x2))",
     "(bvadd x0 x1 (bvnot x2))"},
    {RareRuleKind::FACTOR_BITWISE_AND, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvand (bvand (bvnot (bvand x0 x1)) x2) x0)",
     "(bvand x0 x2 (bvnot x1))"},
    {RareRuleKind::FACTOR_COMMON_BITVECTOR_MULTIPLIER_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvmul x0 x2))",
     "(bvmul x0 (bvadd x1 x2))"},
    {RareRuleKind::FACTOR_COMMON_BIT_VECTOR_MULTIPLICAND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd x2 (bvmul (bvmul x0 x3) x4)))",
     "(bvadd (bvmul x0 (bvadd x1 (bvmul x3 x4))) x2)"},
    {RareRuleKind::FACTOR_COMMON_BV_MUL, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul (bvmul x0 x1) x2) (bvadd (bvmul x2 x3) x4))",
     "(bvadd (bvmul x2 (bvadd (bvmul x0 x1) x3)) x4)"},
    {RareRuleKind::FACTOR_COMMON_BV_MULTIPLY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul (bvmul x0 x1) x2) (bvadd (bvmul x0 x3) x4))",
     "(bvadd (bvmul x0 (bvadd (bvmul x1 x2) x3)) x4)"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) x3))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) x3)"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_10, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) (bvadd (bvmul x0 x3) x4))",
     "(bvadd (bvmul x0 (bvadd x1 x2 x3)) x4)"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvadd x3 x4)))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) (bvadd x3 x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd x2 (bvadd (bvmul x0 x3) x4)))",
     "(bvadd (bvmul x0 (bvadd x1 x3)) (bvadd x2 x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(= x0 (bvadd (bvmul x1 x2) (bvadd (bvmul x1 x3) x4)))",
     "(= x0 (bvadd (bvmul x1 (bvadd x2 x3)) x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_5, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvmul x0 x1) (bvmul x0 x2)) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_6, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(= x0 (bvadd (bvadd (bvmul x1 x2) (bvmul x1 x3)) (@bv 1 (@bvsize x0))))",
     "(= x0 (bvadd (bvmul x1 (bvadd x2 x3)) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_7, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvadd (bvmul x0 x1) x2) (bvadd (bvmul x0 x3) x4))",
     "(bvadd (bvmul x0 (bvadd x1 x3)) (bvadd x2 x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_8, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvmul x3 x4)))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) (bvmul x3 x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLICAND_9, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvmul (bvmul x0 x2) x3))",
     "(bvmul x0 (bvadd x1 (bvmul x2 x3)))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLIER, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd x0 (bvadd (bvmul x1 x2) (bvadd (bvmul x1 x3) x4)))",
     "(bvadd x0 (bvadd (bvmul x1 (bvadd x2 x3)) x4))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLIER_3, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd x2 (bvmul (bvmul x3 x4) x0)))",
     "(bvadd x2 (bvmul x0 (bvadd x1 (bvmul x3 x4))))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLIER_4, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvmul x0 x1) (bvadd (bvmul x0 x2) (bvadd x0 x3)))",
     "(bvadd (bvmul x0 (bvadd x1 x2)) (bvadd x0 x3))"},
    {RareRuleKind::FACTOR_COMMON_MULTIPLIER_5, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvadd (bvadd (bvmul x0 x1) (bvmul (bvmul x0 x2) x3)) x4)",
     "(bvadd (bvmul x0 (bvadd x1 (bvmul x2 x3))) x4)"},
    {RareRuleKind::FACTOR_SHARED_BITWISE_AND, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvand (bvand x0 x1) (bvand (bvnot (bvand (bvand x0 x1) x2)) x3))",
     "(bvand x0 x1 (bvnot x2) x3)"},
    {RareRuleKind::FACTOR_SHARED_XOR_MASK, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec) (x4 ?BitVec))",
     "(bvxor (bvand x0 (bvxor (bvand x1 x2) x3)) (bvxor (bvand x1 x2) x4))",
     "(bvxor (bvand (bvnot x0) (bvand x1 x2)) (bvxor (bvand x0 x3) x4))"},
    {RareRuleKind::FLATTEN_BITVECTOR_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)))",
     "(bvadd x0 x1 x2 (bvnot (@bv 0 (@bvsize x0))))"},
    {RareRuleKind::FLATTEN_BVADD_AND_CANCEL_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))) x2))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::FLATTEN_BVADD_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::FOLD_ADDITIVE_CONSTANTS_BEFORE_NOT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::FOLD_ADDITIVE_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) x2) (bvadd x3 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::FOLD_ARITHMETIC_OFFSETS_BEFORE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::FOLD_BITVECTOR_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::FOLD_BVADD_BVNOT_CONSTANTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd x0 (bvnot x1) (@bv 3 (@bvsize x0)))"},
    {RareRuleKind::FOLD_CANCELLED_ADDENDS_BEFORE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvashr (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) (@bv 1 (@bvsize x0))) x2)",
     "(bvadd (bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0))) x2)"},
    {RareRuleKind::FOLD_COMPLEMENTED_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 x1 (bvnot x2))"},
    {RareRuleKind::FOLD_COMPLEMENTED_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvnot x0) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::FOLD_MINUS_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) x2) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x2 (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::FOLD_MINUS_ONE_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2)) (bvadd x3 (@bv 1 (@bvsize x0))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::FOLD_MINUS_ONE_PLUS_ONE_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 x3))))",
     "(bvadd x0 x1 x2 x3)"},
    {RareRuleKind::FOLD_NEGATED_INCREMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvadd x0 (@bv 1 (@bvsize x0))) (bvxor x1 x2))) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 (bvxor x1 x2)))"},
    {RareRuleKind::FOLD_NEGATIVE_ONE_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) x1))",
     "(bvadd x1 (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::FOLD_NEGATIVE_ONE_AND_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) x2))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1 x2)"},
    {RareRuleKind::GROUPED_ADD_COMPLEMENT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd x2 x3))",
     "(bvnot (bvadd (bvnot (bvadd x0 x1)) (bvnot x2) (bvnot x3) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::INVERT_DECREMENT_EQUALITY, Guard::NOT_NORMAL,
     "((p0 Bool) (p1 Bool) (p2 Bool) (x0 ?BitVec) (x1 ?BitVec))",
     "(and p0 (and (and p1 p2) (= (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)))",
     "(and p0 (and p1 (and p2 (= (bvadd x1 (@bv 1 (@bvsize x0))) x0))))"},
    {RareRuleKind::MERGE_NEGATED_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))) (bvnot x2))",
     "(bvadd x1 (bvnot (bvadd x0 x2)))"},
    {RareRuleKind::MOVE_COMPLEMENTED_ADDEND_ACROSS_EQUALITY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(= x0 (bvadd (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))) x3))",
     "(= (bvadd x0 x2) (bvadd x1 x3))"},
    {RareRuleKind::MOVE_NEGATED_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= x0 (bvadd (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(= (bvadd x0 x2) (bvadd x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::NEGATED_DIFFERENCE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvashr (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvashr (bvadd (bvnot x0) x1) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::NEGATED_SUM_AND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvand x0 x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd (bvand x0 x1) x2))"},
    {RareRuleKind::NEGATED_SUM_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot x0) (bvadd (bvnot x1) (@bv 1 (@bvsize x0))))",
     "(bvnot (bvadd x0 x1))"},
    {RareRuleKind::NEGATED_SUM_REASSOCIATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))) (bvnot x2))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::NORMALIZE_ADDITION_AND_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(not (= x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))",
     "(not (= x0 (bvadd x1 x2)))"},
    {RareRuleKind::NORMALIZE_ADD_NEGATED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (bvadd x1 (bvnot x0)) x2)) x3)",
     "(bvnot (bvadd (bvadd (bvnot x1) (bvnot x2) (bvnot x3)) (@bv 3 (@bvsize x0))))"},
    {RareRuleKind::NORMALIZE_ARITHMETIC_SHIFT_EXPRESSION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0))) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) x1 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::NOT_ASHR_ADD_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvashr (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvashr (bvadd (bvnot x0) (bvnot x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::NOT_OF_THREE_WAY_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) x2)) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::NOT_SUM_VIA_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd x0 (bvadd (bvnot x1) (bvnot x2))))",
     "(bvadd x0 (bvnot (bvadd x1 x2)))"},
    {RareRuleKind::REASSOCIATE_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvadd x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd x2 (bvnot (bvadd x0 x1)))"},
    {RareRuleKind::REMOVE_NEGATIVE_ONE_ADDEND, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0))))",
     "(bvadd x1 (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::REMOVE_ZERO_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd (bvashr x2 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvadd x0 x1) (bvashr x2 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::SIGNED_HALF_PLUS_LOW_BIT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x0 (@bv 1 (@bvsize x0)))))) x1)",
     "(bvadd x1 (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvand x0 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::SIGNED_POSITIVE_INCREMENT_SUM_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvslt (@bv 0 (@bvsize x0)) (bvadd (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1)) (bvadd x2 x3)))",
     "(and (not (bvslt (bvadd x0 x1 x2 x3) (@bv 0 (@bvsize x0)))) (not (= (bvadd x0 x1 x2 x3) (bvlshr (bvnot (@bv 0 (@bvsize x0))) (@bv 1 (@bvsize x0))))))"},
    {RareRuleKind::SIGNED_POSITIVE_OF_SUM_PLUS_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvslt (@bv 0 (@bvsize x0)) (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 (bvadd x2 x3)))))",
     "(and (not (bvslt (bvadd x0 x1 x2 x3) (@bv 0 (@bvsize x0)))) (not (= (bvadd x0 x1 x2 x3) (bvnot (bvshl (@bv 1 (@bvsize x0)) (@bv (- (@bvsize x0) 1) (@bvsize x0)))))))"},
    {RareRuleKind::SIMPLIFY_ADDITIVE_COMPLEMENTS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 x1)) (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))",
     "(bvadd (bvadd x0 x1) (bvnot x2))"},
    {RareRuleKind::SIMPLIFY_ADD_BEFORE_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_ADD_COMPLEMENT_CANCELLATION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0))))) x2)",
     "(bvxor (bvadd (bvnot x0) x1) x2)"},
    {RareRuleKind::SIMPLIFY_ADD_NEGATED_ONE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvxor x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0)))))))",
     "(bvnot (bvxor x0 (bvadd x1 x2)))"},
    {RareRuleKind::SIMPLIFY_ADD_NEGATED_ZERO_OFFSETS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (@bv 1 (@bvsize x0)) (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x1 x2 (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_ALL_ONES_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))))",
     "(bvadd x0 (bvashr (bvadd x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_BIAS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 (bvadd x2 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0))))",
     "(bvadd x0 (bvashr (bvadd x1 x2) (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_EXPRESSION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (bvashr x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 (bvashr x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_ARITHMETIC_SHIFT_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvashr x0 (@bv 1 (@bvsize x0)))) (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) x1) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_COMPLEMENTED_ADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvnot (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0)))))) x2)",
     "(bvadd x2 (bvnot (bvadd x0 x1)))"},
    {RareRuleKind::SIMPLIFY_COMPLEMENTED_SUBTRACTION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvnot x0) (bvadd x1 (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot x0) x1)"},
    {RareRuleKind::SIMPLIFY_COMPLEMENTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvslt (@bv 0 (@bvsize x0)) (bvadd (bvnot (bvadd x0 (bvadd x1 (@bv 1 (@bvsize x0))))) x2))",
     "(bvslt (@bv 0 (@bvsize x0)) (bvadd (bvadd (bvnot x0) (bvnot x1)) x2))"},
    {RareRuleKind::SIMPLIFY_COMPLEMENTED_SUM_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvashr (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1)) (@bv 1 (@bvsize x0))))",
     "(bvashr (bvadd (bvnot x0) (bvnot x1) (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_NEGATED_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvnot (@bv 0 (@bvsize x0))) (bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvadd (bvnot x1) (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvashr x0 (@bv 1 (@bvsize x0))) (bvnot x1))"},
    {RareRuleKind::SIMPLIFY_NEGATED_ADD_ONES, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x1) (bvadd x2 (@bv 1 (@bvsize x0))))))",
     "(bvnot (bvadd x0 x1 x2))"},
    {RareRuleKind::SIMPLIFY_NEGATED_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0))) x1)",
     "(bvadd (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) x1)"},
    {RareRuleKind::SIMPLIFY_NEGATED_ARITHMETIC_SHIFT_2, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvadd (bvnot (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvadd (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_NEGATED_SHIFTED_SUM, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0))))",
     "(bvashr (bvnot (bvadd x0 x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_NEGATED_ZERO_ADDENDS, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvadd x1 (@bv 1 (@bvsize x0)))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x1 (bvnot x0)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_NEGATIVE_SHIFTED_COMPLEMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd (bvashr (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (@bv 1 (@bvsize x0))) (bvadd x1 x2))",
     "(bvadd (bvnot (bvashr (bvadd x0 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))) (bvadd x1 x2))"},
    {RareRuleKind::SIMPLIFY_NESTED_BVADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (@bv 1 (@bvsize x0)) (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd x1 (@bv 1 (@bvsize x0))))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 (@bv 1 (@bvsize x0))) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_NESTED_COMPLEMENT_ADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvnot (bvadd x1 (bvadd (bvnot x2) (@bv 1 (@bvsize x0))))))",
     "(bvadd x0 x2 (bvnot x1))"},
    {RareRuleKind::SIMPLIFY_NOT_ADD_NEGATED_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvnot (bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvashr x1 (@bv 1 (@bvsize x0)))))))",
     "(bvadd (bvnot x0) (bvashr x1 (@bv 1 (@bvsize x0))))"},
    {RareRuleKind::SIMPLIFY_OFFSET_SUM_ARITHMETIC_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x1 x2))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 x1 x2) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SIMPLIFY_SHIFTED_DOUBLE_ADD, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvashr (bvadd (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) (bvadd (@bv 1 (@bvsize x0)) (bvadd x0 x1))) (@bv 1 (@bvsize x0)))",
     "(bvashr (bvadd x0 (bvadd x0 x1)) (@bv 1 (@bvsize x0)))"},
    {RareRuleKind::SUBTRACTION_VIA_COMPLEMENTED_ADDITION, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec))",
     "(bvadd (bvadd x0 (bvnot x1)) (@bv 1 (@bvsize x0)))",
     "(bvnot (bvadd (bvnot x0) x1))"},
    {RareRuleKind::XOR_AND_DISTRIBUTION_FACTOR, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvxor (bvand (bvxor x0 x1) (bvxor x0 x2)) (bvxor x0 x3))",
     "(bvxor (bvand x0 (bvxor x1 x2)) (bvand x1 x2) x3)"},
    {RareRuleKind::XOR_COMPLEMENT_ADD_TO_SUB, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvadd x0 (bvadd (@bv 1 (@bvsize x0)) (bvnot (bvxor x1 x2))))",
     "(bvnot (bvadd (bvnot x0) (bvxor x1 x2)))"},
    {RareRuleKind::XOR_MASK_COMBINE, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvxor (bvxor x0 (bvxor x1 x2)) (bvand x3 (bvxor x0 x1)))",
     "(bvxor x2 (bvand (bvxor x0 x1) (bvnot x3)))"},
    {RareRuleKind::XOR_MUX_DISTRIBUTION, Guard::NONE,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec) (x3 ?BitVec))",
     "(bvxor (bvand x0 (bvxor x1 x2)) (bvxor x1 x3))",
     "(bvxor (bvxor (bvand x0 x2) (bvand (bvnot x0) x1)) x3)"},
    {RareRuleKind::XOR_NEGATED_DECREMENT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvxor x0 (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot (bvxor (bvand x1 x2) x0))))",
     "(bvnot (bvxor x0 (bvadd (bvxor (bvand x1 x2) x0) (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::XOR_NEGATION_ADD_REWRITE, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(bvnot (bvadd (bvxor x0 x1) (bvadd (bvnot x2) (@bv 1 (@bvsize x0)))))",
     "(bvadd (bvnot (bvxor x0 x1)) x2)"},
    {RareRuleKind::XOR_NOT_DECREMENT_PATTERN, Guard::NOT_NORMAL,
     "((x0 ?BitVec))",
     "(bvxor x0 (bvand (bvadd (bvnot (@bv 0 (@bvsize x0))) (bvnot x0)) (bvnot x0)))",
     "(bvnot (bvand (bvnot x0) (bvadd x0 (@bv 1 (@bvsize x0)))))"},
    {RareRuleKind::XOR_SUBTRACT_ONE_EQUALITY, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= (bvxor (bvadd (bvnot (@bv 0 (@bvsize x0))) x0) x1) x2)",
     "(= (bvadd (bvxor x1 x2) (@bv 1 (@bvsize x0))) x0)"},
    {RareRuleKind::ZERO_AFTER_LEFT_SHIFT, Guard::NOT_NORMAL,
     "((x0 ?BitVec) (x1 ?BitVec) (x2 ?BitVec))",
     "(= (@bv 0 (@bvsize x0)) (bvshl x0 (bvadd x1 x2)))",
     "(= (bvand x0 (bvlshr (bvnot (@bv 0 (@bvsize x0))) (bvadd x1 x2))) (@bv 0 (@bvsize x0)))"},
};
// clang-format on

}  // namespace bzla::test
