-- CS F214 Assignment 1 Part B
-- Book examples 1 13 to 1 18 proved in Lean 4
-- The premise of each sequent is the hypothesis h
-- The conclusion of each sequent is the goal after the colon
-- And p q means p and q
-- Or p q means p or q
-- p -> q means p implies q

-- Example 1 13
-- From p and q implies r prove p implies q implies r
theorem example_1_13 (p q r : Prop) (h : And p q -> r) : p -> (q -> r) := by
  intro hp
  intro hq
  have hpq : And p q := And.intro hp hq
  exact h hpq

-- Example 1 14
-- From p implies q implies r prove p and q implies r
theorem example_1_14 (p q r : Prop) (h : p -> (q -> r)) : And p q -> r := by
  intro hpq
  have hp : p := hpq.left
  have hq : q := hpq.right
  exact h hp hq

-- Example 1 15
-- From p implies q prove p and r implies q and r
theorem example_1_15 (p q r : Prop) (h : p -> q) : And p r -> And q r := by
  intro hpr
  have hp : p := hpr.left
  have hr : r := hpr.right
  have hq : q := h hp
  exact And.intro hq hr

-- Example 1 16
-- From q implies r prove p or q implies p or r
theorem example_1_16 (p q r : Prop) (h : q -> r) : Or p q -> Or p r := by
  intro hpq
  cases hpq with
  | inl hp => exact Or.inl hp
  | inr hq => exact Or.inr (h hq)

-- Example 1 17
-- From p or q or r with p or q in brackets prove p or q or r with q or r in brackets
theorem example_1_17 (p q r : Prop) (h : Or (Or p q) r) : Or p (Or q r) := by
  cases h with
  | inl hpq =>
    cases hpq with
    | inl hp => exact Or.inl hp
    | inr hq => exact Or.inr (Or.inl hq)
  | inr hr => exact Or.inr (Or.inr hr)

-- Example 1 18
-- From p and q or r prove p and q or p and r
theorem example_1_18 (p q r : Prop) (h : And p (Or q r)) : Or (And p q) (And p r) := by
  have hp : p := h.left
  have hqr : Or q r := h.right
  cases hqr with
  | inl hq => exact Or.inl (And.intro hp hq)
  | inr hr => exact Or.inr (And.intro hp hr)
