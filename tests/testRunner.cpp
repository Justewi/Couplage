#include <cstdlib>
void bipartite_matching_multiple_iterations();
void bipartite_matching_two_left_options();
void bipartite_matching_all_on_one_right();
void bipartite_matching_disjoint();
void is_perfect_match_not_even_a_match();
void is_perfect_match_false();
void is_perfect_match_true();
void maximum_matching();
void maximum_matching_not_fully_connected();
void maximum_matching_star();
void maximum_matching_blossom();
void bipartite_matching_multiple_iterations_g();
void bipartite_matching_two_left_options_g();
void bipartite_matching_all_on_one_right_g();
void bipartite_matching_disjoint_g();

using namespace std;

int main(int argc, char** argv) {
    bipartite_matching_multiple_iterations();
    bipartite_matching_two_left_options();
    bipartite_matching_all_on_one_right();
    bipartite_matching_disjoint();
    is_perfect_match_not_even_a_match();
    is_perfect_match_false();
    is_perfect_match_true();

    maximum_matching();
    maximum_matching_not_fully_connected();
    maximum_matching_star();
    maximum_matching_blossom();

    bipartite_matching_multiple_iterations_g();
    bipartite_matching_two_left_options_g();
    bipartite_matching_all_on_one_right_g();
    bipartite_matching_disjoint_g();
    return 0;
}
