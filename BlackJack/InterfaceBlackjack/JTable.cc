#include "JTable.h"
#include <cassert>

const JTable::Hand& JTable::GetHand(int player_index, int hand_index) const{
  return hands_[player_index][hand_index];
}

int JTable::GetNumberOfHands(int player_index) const{
  return hands_[player_index].size();
}

int JTable::GetPlayerCurrentBet(int player_index,int hand_index) const{
  return player_bets_[player_index][hand_index];
}

int JTable::GetPlayerMoney(int player_index) const{
  return total_player_money_[player_index];
}

void JTable::SetPlayerInitialBet(int player_index,int money) {
  player_bets_[player_index][0] = money;
}

JTable::Card JTable::GetDealerCard() const{

  if(crupier_hand.empty()){

    return {Value::end, Suit::end};
  }

  return crupier_hand[0];
}

int JTable::CroupierMoney() const{
    
    return crupier_money;
}



void JTable::DealCard(int player_index, int hand_index){
  
    //.back = ultimo dato del vector
    //.puch_back = mete un dato al final del vector
    //.pop_back = borra un dato al final del vector


}
        
void JTable::PlaySafeBet(int player_index){
    
    //Comprobar Ace en crupier
    //Calcular coste seguro 
    //Validar saldo del player
    //Actualizar dinero del player y del crupier
    //Guardar registro del seguro (opcional)
}

JTable::Result JTable::ApplyPlayerAction(int player_index,int hand_index,Action action){


    // Verificar que los indices sean validos

    // Acciones : Stand, Hit, Double, Split

    // Stand marcara la mnao como "cerrada", no se modifican dinero ni cartas, retorna OK

    // Hit llamara a DealCard, evaluara el valor total de la mano si el valor es mayor que 21 marcar como "bust", retorna OK

    // Double comprobara que la mano tenga dos cartas, verificara el saldo del player > apuesta incial, actualiza el dinero del player y del crupier
    // duplica la puesta de la mano, llama a DealCard, marca la mano como cerrada, retorna OK

    // Split comprobara que la mano tenga dos cartas, que ambas cartas sean del mismo valor, verifica el saldo del jugador > apuesta inicial, 
    // crea una nueva mano, copia la apuesta original a la nueva mano, actualizar dinero player y crupier, llama a DealCard y reparte a cada una de las manos
    // si son ases marca ambas manos como cerradas, retorna OK

    // Si alguna accion no cumple las condiciones retornar Result::Ilegal
    
}


void JTable::StartRound(){

}

JTable::RoundEndInfo JTable::FinishRound(){

}