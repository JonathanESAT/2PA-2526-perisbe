#include <vector>

class ITable {
    public:
        enum class Action {
            Stand,
            Hit,
            Double,
            Split
        };

        enum class Result {
            Ok,
            Illegal
        };
        enum class Value {
            ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING,
            end
        };

        enum class Suit {
            HEARTS,
            CLUBS,
            SPADES,
            DIAMONDS,
            end
        };

        struct Card {
            Value value_;
            Suit suit_;
        };

        using Hand = std::vector<Card>;


        class RoundEndInfo {
            Hand croupier_hand;
            std::vector<bool> winners;
            std::vector<int> money_delta; // El dinero ganado por el jugador en esta ronda(no se pierde aqui
                                        // , porque el dinero ya se ha quitado al hacer la apuesta).
            int money_delta; // El dinero ganado o perdido por el croupier en esta ronda
        };

        static const int kMaxBet = 10000;
        static const int kMinBet = 100;
        static const int kPlayerStartMoney = 4000;
        static const int kCroupierStartMoney = 100000;
        static const int kCroupierStop = 17;
        static const int kMaxPlayers = 7; // Si se os agotan las cartas en una ronda, bajad el maximo de jugadores

        virtual const Hand& GetHand(int player_index,int hand_index) const = 0;
        virtual int GetNumberOfHands(int player_index) const = 0;

        virtual int GetPlayerCurrentBet(int player_index,int hand_index) const = 0;
        virtual int GetPlayerMoney(int player_index) const = 0;
        virtual void SetPlayerInitialBet(int player_index,int money) = 0;

        virtual Card GetDealerCard() const = 0;

        virtual int CroupierMoney() const = 0;

        // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
        virtual void DealCard(int player_index,int hand_index) = 0;

        virtual void PlaySafeBet(int player_index) = 0;
        virtual Result ApplyPlayerAction(int player_index,int hand_index,Action action) = 0;


        virtual void StartRound() = 0;

        virtual RoundEndInfo FinishRound() = 0;
        
        virtual ~ITable() = default;
};