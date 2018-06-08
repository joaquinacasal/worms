#ifndef __MYTESTSUITE_H
#define __MYTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include "src/server/server_Stage.h"
#include "src/server/server_TurnsManager.h"
#include "src/server/server_Armory.h"
#include <chrono>
#include <thread>


class WormTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 1000;
  size_t id = 15;
  size_t life = 100;
  size_t initial_position_x = 500;
  size_t initial_position_y = 10;
public:
    void testConstructorDelGusano( void )
    {
      std::string description = "Test de creación del gusano";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      TS_ASSERT_EQUALS( id, actual_worm->get_id() );
      actual_worm->subtract_life(50);
      TS_ASSERT( actual_worm->is_alive() );
      actual_worm->subtract_life(50);
      TS_ASSERT( !actual_worm->is_alive() );
      TS_ASSERT_EQUALS( initial_position_x, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( 0, actual_worm->get_horizontal_velocity() );
      TS_ASSERT_EQUALS( 0, actual_worm->get_vertical_velocity() );
      TS_ASSERT_EQUALS( 0, actual_worm->get_angle() );

      std::cout << "EXITOSO\n";
    }

    void testCaidaPorLaGravedad( void )
    {
      std::string description = "Test de caida del gusano por la gravedad";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      for (size_t i = 0; i < 10000; i++){
        st.step(actual_worm);
      }
      TS_ASSERT_DELTA( 2, actual_worm->get_vertical_position(), 0.1f );

      std::cout << "EXITOSO\n";
    }

    void testSaltoParaAdelante( void )
    {
      std::string description = "Test del salto para adelante";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      float altura_maxima = -100;
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      for (size_t i = 0; i < 1000; i++){
        st.step(actual_worm);
      }
      actual_worm->jump_forward();
      for (size_t i = 0; i < 10000; i++){
        st.step(actual_worm);
        if (actual_worm->get_vertical_position() > altura_maxima) altura_maxima = actual_worm->get_vertical_position();
      }
      TS_ASSERT_DELTA( initial_position_x + 10, actual_worm->get_horizontal_position(), 0.2f );
      TS_ASSERT_DELTA( 2 + 5, altura_maxima, 0.2f );
      std::cout << "EXITOSO\n";
    }

    void testSaltoParaAtras( void )
    {
      std::string description = "Test del salto para atrás";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      float altura_maxima = -100;
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      for (size_t i = 0; i < 1000; i++){
        st.step(actual_worm);
      }
      actual_worm->jump_backward();
      for (size_t i = 0; i < 10000; i++){
        st.step(actual_worm);
        if (actual_worm->get_vertical_position() > altura_maxima) altura_maxima = actual_worm->get_vertical_position();
      }
      TS_ASSERT_DELTA( initial_position_x - 2, actual_worm->get_horizontal_position(), 0.2f );
      TS_ASSERT_DELTA( 14, altura_maxima, 0.2f );

      std::cout << "EXITOSO\n";
    }

    void testMoverseALaDerecha( void )
    {
      std::string description = "Test de caminar para la derecha";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      actual_worm->move_right();
      for (size_t i = 0; i < 15000; i++){
        st.step(actual_worm);
        if (i > 100 && i < 1000 && i%100 == 0)
          TS_ASSERT_DELTA( 2, actual_worm->get_horizontal_velocity(), 0.3f );
      }
      TS_ASSERT_DELTA( ancho_stage, actual_worm->get_horizontal_position(), 3.0f );

      std::cout << "EXITOSO\n";
    }

    void testMoverseALaIzquierda( void )
    {
      std::string description = "Test de caminar para la izquierda";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      actual_worm->move_left();
      for (size_t i = 0; i < 15000; i++){
        st.step(actual_worm);
        if (i > 100 && i < 1000 && i%100 == 0)
          TS_ASSERT_DELTA( -2, actual_worm->get_horizontal_velocity(), 0.3f );
      }
      TS_ASSERT_DELTA( 0 , actual_worm->get_horizontal_position(), 3.0f );
      std::cout << "EXITOSO\n";
    }

    void testCaerSobreUnaViga( void )
    {
      std::string description = "Test de caer sobre una viga";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_beam(id, 10, initial_position_x, 4, 0);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* actual_worm = st.get_worm(id);
      for (size_t i = 0; i < 1000; i++){
        st.step(actual_worm);
      }
      TS_ASSERT_DELTA( 10, actual_worm->get_vertical_position(), 0.2f );
      std::cout << "EXITOSO\n";

    }
};

class BeamTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 1000;
  size_t id1 = 1;
  size_t id2 = 2;
  size_t angle1 = 0;
  size_t angle2 = 90;
  size_t initial_position_x = 10;
  size_t initial_position_y = 10;
  size_t largo_viga = 10;
public:
    void testConstructorDeLaViga( void )
    {
      std::string description = "Test de creación de la viga";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_beam(id1, largo_viga, initial_position_x, initial_position_y, angle1);
      st.add_beam(id2, largo_viga, initial_position_x, initial_position_y, angle2);
      Beam* b1 = st.get_beam(id1);
      Beam* b2 = st.get_beam(id2);

      TS_ASSERT_EQUALS( id1, b1->get_id() );
      TS_ASSERT_EQUALS( id2, b2->get_id() );

      TS_ASSERT_EQUALS( initial_position_x, b1->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_x, b2->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y, b1->get_vertical_position() );
      TS_ASSERT_EQUALS( initial_position_y, b2->get_vertical_position() );
      TS_ASSERT_EQUALS( largo_viga, b1->get_length() );
      TS_ASSERT_EQUALS( largo_viga, b2->get_length() );
      TS_ASSERT_EQUALS( 8, b1->get_width() );
      TS_ASSERT_EQUALS( 8, b2->get_width() );
      TS_ASSERT_EQUALS( angle1, b1->get_angle() );
      TS_ASSERT_EQUALS( angle2, b2->get_angle() );
      std::cout << "EXITOSO\n";

    }
};


class TurnsManagerTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 1000;
  size_t life = 100;
  size_t initial_position_x = 0;
  size_t initial_position_y = 10;

public:
    void testManejadorDeTurnos( void )
    {
      std::string description = "Test de creación del Manejador de Turnos";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      TurnsManager tm;
      Worm* arr_worms[15];
      Player* arr_players[5];
      for (size_t i = 0; i < 5; i++){
        Armory* armory = new Armory(st);
        arr_players[i] = new Player(armory);
      }

      for (size_t i = 0; i < 15; i++){
        st.add_worm(i, life, initial_position_x, initial_position_y);
        arr_worms[i] = st.get_worm(i);
      }

      for (size_t i = 0; i < 15; i++){
        arr_players[i%5]->add_worm(arr_worms[i]);
      }

      for (size_t i = 0; i < 5; i++){
        tm.add_player(arr_players[i]);
      }

      for (size_t i = 0; i < 15; i++){
        Player* temp_player = tm.get_selected_player();
        Worm* temp_worm = temp_player->get_selected_worm();
        TS_ASSERT_EQUALS( temp_worm->get_id(), arr_worms[i%15]->get_id() );
        tm.finish_turn();
      }
      std::cout << "EXITOSO\n";
    }

    void testCambioDeTurnosConGusanos( void ) {
      std::string description = "Test de cambio de turnos con muchos gusanos";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      Armory* armory1 = new Armory(st);
      Armory* armory2 = new Armory(st);

      st.add_worm(1, life, 100, 10);
      st.add_worm(2, life, 200, 10);
      st.add_worm(3, life, 300, 10);
      st.add_worm(4, life, 400, 10);
      Player* player1 = new Player(armory1);
      Player* player2 = new Player(armory2);
      player1->add_worm(st.get_worm(1));
      player2->add_worm(st.get_worm(2));
      player1->add_worm(st.get_worm(3));
      player2->add_worm(st.get_worm(4));
      TurnsManager tm;
      tm.add_player(player1);
      tm.add_player(player2);

      for (size_t i = 0; i < 4000; i++){
        Player* actual_player = tm.get_selected_player();
        Worm* actual_worm = actual_player->get_selected_worm();
        TS_ASSERT_EQUALS( i%4 + 1, actual_worm->get_id() );
        tm.finish_turn();
      }
      std::cout << "EXITOSO\n";

    }
};

class TeletransportationTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 1000;
  size_t id = 1;
  size_t life = 1000;
  size_t initial_position_x = 10;
  size_t initial_position_y = 10;

public:
    void testTeletransportacionUnSoloGusano( void )
    {
      std::string description = "Test de la teletransportación con un solo gusano";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* worm = st.get_worm(id);
      Armory* armory = new Armory(st);
      Player* player = new Player(armory);
      player->add_worm(worm);
      TurnsManager tm;
      tm.add_player(player);

      Worm* actual_worm = tm.get_selected_player()->get_selected_worm();
      TS_ASSERT_EQUALS( initial_position_x, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 5 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 5, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 5, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 4 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 3 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 15, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 15, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 2 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 20, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 20, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 1 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 25, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 25, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 0 );

      player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( initial_position_x + 25, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( initial_position_y + 25, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( player->get_teletransportation_munitions(), 0 );

      std::cout << "EXITOSO\n";
    }

    void testTeletransportacionMuchosGusanos( void )
    {
      std::string description = "Test de la teletransportación con muchos gusanos";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(1, life, 100, 10);
      st.add_worm(2, life, 200, 10);
      st.add_worm(3, life, 300, 10);
      st.add_worm(4, life, 400, 10);
      Armory* armory1 = new Armory(st);
      Armory* armory2 = new Armory(st);
      Player* player1 = new Player(armory1);
      Player* player2 = new Player(armory2);
      player1->add_worm(st.get_worm(1));
      player1->add_worm(st.get_worm(2));
      player2->add_worm(st.get_worm(3));
      player2->add_worm(st.get_worm(4));
      TurnsManager tm;
      tm.add_player(player1);
      tm.add_player(player2);

      // Verificación de la creación
      // worm con id 1
      Player* actual_player = tm.get_selected_player();
      Worm* actual_worm = actual_player->get_selected_worm();
      TS_ASSERT_EQUALS( 1, actual_worm->get_id() );
      TS_ASSERT_EQUALS( 100, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 5 );
      tm.finish_turn();

      // worm con id 3
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      TS_ASSERT_EQUALS( 3, actual_worm->get_id() );
      TS_ASSERT_EQUALS( 300, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 5 );
      tm.finish_turn();

      // worm con id 2
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      TS_ASSERT_EQUALS( 2, actual_worm->get_id() );
      TS_ASSERT_EQUALS( 200, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 5 );
      tm.finish_turn();

      // worm con id 4
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      TS_ASSERT_EQUALS( 4, actual_worm->get_id() );
      TS_ASSERT_EQUALS( 400, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 5 );
      tm.finish_turn();


      // Aplicamos las teletransportaciones
      // worm con id 1
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 100 + 5, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 5, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 4 );
      tm.finish_turn();

      // worm con id 3
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 300 + 5, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 5, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 4 );
      tm.finish_turn();

      // worm con id 2
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 200 + 5, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 5, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 3 );
      tm.finish_turn();

      // worm con id 4
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 400 + 5, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 5, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 3 );
      tm.finish_turn();

      // worm con id 1
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 100 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 2 );
      tm.finish_turn();

      // worm con id 3
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 300 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 2 );
      tm.finish_turn();

      // worm con id 2
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 200 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 1 );
      tm.finish_turn();

      // worm con id 4
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 400 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 1 );
      tm.finish_turn();

      // worm con id 1
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 100 + 15, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 15, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 0 );
      tm.finish_turn();

      // worm con id 3
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 300 + 15, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 15, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 0 );
      tm.finish_turn();

      // worm con id 2
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 200 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 0 );
      tm.finish_turn();

      // worm con id 4
      actual_player = tm.get_selected_player();
      actual_worm = actual_player->get_selected_worm();
      actual_player->teletransport_actual_worm(actual_worm->get_horizontal_position() + 5, actual_worm->get_vertical_position() + 5);
      TS_ASSERT_EQUALS( 400 + 10, actual_worm->get_horizontal_position() );
      TS_ASSERT_EQUALS( 10 + 10, actual_worm->get_vertical_position() );
      TS_ASSERT_EQUALS( actual_player->get_teletransportation_munitions(), 0 );
      tm.finish_turn();

      std::cout << "EXITOSO\n";
    }
};

class DynamiteTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 1000;
  size_t id = 1;
  size_t life = 100;
  size_t initial_position_x = 10;
  size_t initial_position_y = 3;
public:
    void testExplosionDinamita( void )
    {
      std::string description = "Test de explosión de la dinamita";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* worm = st.get_worm(id);
      Armory* armory = new Armory(st);
      Player* player = new Player(armory);
      player->add_worm(worm);
      TS_ASSERT( !player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 5 );

      // Wait till hits the floor
      for (size_t i = 0; i < 1000; i++){
        st.step(worm);
      }
      // Activate dynamite
      TS_ASSERT( player->use_dynamite() );
      TS_ASSERT( player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 4 );

      // Try to activate again
      TS_ASSERT( !player->use_dynamite() );
      TS_ASSERT( player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 4 );


      // wait till explodes
      auto start_dynamite = std::chrono::steady_clock::now();
      player->discount_dynamite_time(6999);
      TS_ASSERT( !player->use_dynamite() );
      TS_ASSERT( player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 4 );
      TS_ASSERT_EQUALS( 100, worm->get_life_points() );


      player->discount_dynamite_time(2);
      TS_ASSERT( !player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 4 );
      TS_ASSERT( player->use_dynamite() );
      TS_ASSERT( player->is_dynamite_active() );
      TS_ASSERT_EQUALS( player->get_dynamite_munitions(), 3 );
      TS_ASSERT_DELTA( 50, worm->get_life_points(), 5 );

      std::cout << "EXITOSO\n";
    }
};


class RadiocontrolledTest : public CxxTest::TestSuite
{
  size_t ancho_stage = 1000;
  size_t largo_stage = 100;
  size_t id = 1;
  size_t life = 100;
  size_t initial_position_x = 800;
  size_t initial_position_y = 3;
public:
    void testCaidaRadiocontrolled( void )
    {
      std::string description = "Test de caida del teledirigido";
      std::cout << "\nIniciando test: '" << description << "' ... ";
      TS_TRACE(description);
      Stage st(ancho_stage, largo_stage);
      st.add_worm(id, life, initial_position_x, initial_position_y);
      Worm* worm = st.get_worm(id);
      Armory* armory = new Armory(st);
      Player* player = new Player(armory);
      player->add_worm(worm);
      TS_ASSERT( !player->is_radiocontrolled_active() );

      // Wait till hits the floor
      for (size_t i = 0; i < 1000; i++){
        st.step(worm);
      }
      // Activate radiocontrolled
      TS_ASSERT( player->use_radiocontrolled(initial_position_x) );
      TS_ASSERT( player->is_radiocontrolled_active() );
      // Try to activate again
      TS_ASSERT( !player->use_radiocontrolled(initial_position_x) );
      TS_ASSERT( player->is_radiocontrolled_active() );


      // Chequeo posición inicial
      std::vector<std::pair<float,float>> positions = player->get_radiocontrolled_positions();
      for (size_t i = 0; i < 6; i++) {
        TS_ASSERT_DELTA( positions[i].first, initial_position_x - 50 * (2.5 - i), 1);
        TS_ASSERT_DELTA( positions[i].second, largo_stage - 10, 1);

      }

      for (size_t i = 0; i < 300; i++){
        st.step(worm);
        player->check_radiocontrolled_explosions();
        if (!player->is_radiocontrolled_active()){
          break;
        }
      }
      TS_ASSERT( worm->get_life_points() < 100);
      TS_ASSERT( !player->is_radiocontrolled_active() );

      //TS_ASSERT_DELTA( player->get_radiocontrolled_horizontal_position(), initial_position_x, 1);
      //TS_ASSERT_DELTA( player->get_radiocontrolled_vertical_position(), 4, 1);

      std::cout << "EXITOSO\n";
    }
};

#endif
