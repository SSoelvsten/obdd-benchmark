#include "common.cpp"
#include "pigeonhole_principle.cpp"

#include "coom_init.cpp"

// =============================================================================
int main(int argc, char** argv)
{
  size_t N = 8;
  size_t M = 128;
  parse_input(argc, argv, N, M);

  // =========================================================================
  INFO("Pigeonhole Principle for %zu : %zu (COOM %zu MB):\n", N+1, N, M);
  coom_init(M);

  // =========================================================================
  coom_sat_solver solver(label_of_Pij(N+1, N, N));
  auto t1 = get_timestamp();
  construct_PHP_cnf(solver, N);
  auto t2 = get_timestamp();

  auto t3 = get_timestamp();
  bool satisfiable = solver.check_satisfiable();
  auto t4 = get_timestamp();

  // =========================================================================
  INFO(" | solution:            %s\n", satisfiable ? "SATISFIABLE" : "UNSATISFIABLE");
  INFO(" | CNF:\n");
  INFO(" | | variables:\n");
  INFO(" | | | total:           %zu\n", solver.var_count());
  INFO(" | | | quantified:      %zu\n", solver.exists_count());
  INFO(" | | clauses:\n");
  INFO(" | | | total:           %zu\n", solver.cnf_size());
  INFO(" | | | done:            %zu\n", solver.apply_count());
  INFO(" | BDD size (nodes):\n");
  INFO(" | | largest size:      %zu\n", solver.bdd_largest_size());
  INFO(" | | final size:        %zu\n", solver.bdd_size());
  INFO(" | time (ms):\n");
  INFO(" | | CNF construction:  %zu\n", duration_of(t1,t2));
  INFO(" | | BDD solving:       %zu\n", duration_of(t3,t4));

  // =========================================================================
  INFO(" | solution:            %s\n", satisfiable ? "SATISFIABLE" : "UNSATISFIABLE");

  coom_deinit();

  exit(satisfiable ? -1 : 0);
}
