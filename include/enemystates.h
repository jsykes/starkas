#ifndef ENEMYSTATES_H
#define ENEMYSTATES_H
/*
 *  EnemyStates.h
 * 
 *	Inherit from this for agents to have FSM functionality
 *	
 *
 *  Created by John Sykes & Daniel O'Sullavan on 5/13/10.
 *  Copyright 2010.
 *
 */
 
 class Enemy;
 
 
 
 class Move
{
private:
  
  Move(){}

  //copy ctor and assignment should be private
  Move(const Move&);
  Move& operator=(const Move&);
 
public:

  //this is a singleton
  static Move* Instance();
  
  virtual void Enter(Enemy* enemy);

  virtual void Execute(Enemy* enemy);

  virtual void Exit(Enemy* enemy);

};

#endif