#include <gtest/gtest.h>

extern "C" {
#include "game_logic.h"
}

class GameLogicTest : public ::testing::Test {
protected:
    GameState state{};

    void SetUp() override {
        initialize_state(&state);
    }
};

TEST_F(GameLogicTest, XHorizontalWin) {
    state.grid[0][0] = PLAYER_X;
    state.grid[1][1] = PLAYER_X;
    state.grid[2][2] = PLAYER_X;
    EXPECT_TRUE(check_win_condition(&state, PLAYER_X));
}

TEST_F(GameLogicTest, OHorizontalWin) {
    state.grid[0][0] = PLAYER_O;
    state.grid[1][1] = PLAYER_O;
    state.grid[2][2] = PLAYER_O;
    EXPECT_TRUE(check_win_condition(&state, PLAYER_O));
}

TEST_F(GameLogicTest, Stalemate) {
    for (auto &i: state.grid)
        for (auto &j: i)
            j = PLAYER_X;

    state.winning_player = EMPTY;
    EXPECT_TRUE(check_stalemate_condition(&state));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
