#include<iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

char usrexit =0;
int wallet=100;
int roll;
int intel=0,charism=0,strength=0;
int highrisk=40,medrisk=25,lowrisk=5,insanerisk=400;                                           //risk values for search function.
string Streets = "Streets", Citadel = "Citadel", Palacex = "Palace", Fortx = "Fort", Marketx = "Market", Mosquex = "Mosque",Coffeex = "Coffee House";    //Main Locations
string loc[7] = {Streets, Citadel, Palacex, Fortx, Marketx, Mosquex,Coffeex};   
bool streetinter1=false, streetinter2=false;                                                          //checks if interactions have happened (to avoid repeats of the same interaction, provided user has taken part in all)        
bool DjinnInteraction = false;
bool MosqueManInteraction=false;
bool GeneralInteraction = false;
bool QaziInteraction = false;
bool CoffeeOwnerInteraction = false;
bool ownerkilled = false;
bool CultInteraction = false;
bool scholarinteraction = false;
bool sultaninteraction = false;
bool sultanoffense = false;
bool yellowhouse = false;
int  phase = 1;        
bool hint1 = false, hint2 = false;                                                                                 //for objectives function
bool extortflag = false;                                                    //protection money at the coffeehouse
int UserMenu(int i);
void Stats(int i);
void Search(int j, int r);
void Prison(int r);
void market_init(int j);
void Citadelin();
bool ChanceEncounter();
void Mosque();
void Palace();

//endgame condition flags (attributes also a factor)
bool cult=0,caliph=0,artpos=0,artkno=0,dead=0;

string palref = "void";

string inventory_type[6] = {"Clothes", "Dagger", "Poison", "Ration", "Artifact", "Books"};   //user inventory
int inventory_amount[6] = {1, 0, 0, 2, 0, 0};

string market_inventory_type[6] = {"Clothes", "Dagger", "Poison", "Ration", "Artifact", "Books"};   //market
int market_inventory_capacity[6] = {3, 2, 1, 12, 0, 2};
int market_fund = 10000;
const int price_[6] = {500, 350, 500, 20, 20000, 100};

void endings(int x){
    switch (x)
    {
    case 1:
        cout<<"A cowards way out, you are able flee the fort, reaching the citadel. Seeing the gated society now overrun with insurgent troops, you retreat back to the town where it all began. However it seems you have run out of luck when the town hails the new insurgents as great inquisitors."<<endl<<endl;
        cout<<"You have no where to go, definitely not home." << endl<<endl <<"The cult makes the caliphate a miserable place to live; Music is banned, dancing is banned, art is banned, games are banned, any religious practice slightly deviating from the norm is banned."<<endl<<endl;
        cout <<"The economy is in ruins, and you live the rest of your life as a lowly assistant in the market under the boot of a tyrannical regime.";
                    do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        break;
    
    case 2:
        cout<<"Adrenaline takes over your body. Everything becomes a blur, but when the dust settles, all those left standing are you and the insurgency leader. He tries to amend this by striking first, but you easily overcome him,holding him in position. He quickly realises his predicament and surrenders. You walk outside the fort with the leader captured. The onlooking army sees their enigmatic leader weak and quickly follow in submission."<<endl<<endl;
        cout<<"Days pass and by the testimony of the "<<palref<<" celebrates you as a great defender of the Caliphate. The Sultan enlist you into his personal guard."<<endl<<endl ;
        if (artkno==true){
            cout<<"You know what the artifact does, that it is the reason why you are here."<<endl<<endl<<"You sneak into the fort to claim the artifact. It's inscriptions remind you of what the Djinn revealed to you. They begin to glow, a light so intense you are forced to close your eyes."<<endl<<endl << "You awake in your slipknot T-shirt shirt once again. You turn on your lamp, everything is where it's supposed to be. The nightmare is over, you are home.";
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
        else{
            cout<<"You know the artifact is the cause of you waking up here. However, because of your inability to use it, you are forced to spend the rest of your life here. "<<endl<<endl;
            cout << "Since you have the Sultan's favour and are now a man of means, you are able to make a life for yourself. You buy a house in the citadel, marry someone you think you are in love with and try to raise a family. You marry once again when you find out you can have up to four wives. You travel often, you are deeply learned, but something still feels missing." << endl << endl;
            cout << "Something feels wrong. You never really get used to the food, the hobbies, the spirit of this era. It is just not where you belong." ;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
        break;

    case 3:
        cout<<"You hand over the artifact."<<endl<<endl<<"\"You have been perfect in your role. You are one of us. You will be my vicegerent.\""<<endl<<endl;
        cout<<"You rule alongside him, never to be content. The cult makes the caliphate a miserable place to live; Music is banned, dancing is banned, art is banned, games are banned, any religious practice slightly deviating from the norm is banned."<<endl<<endl;
        cout << "Even as viceregent, you are deeply unhappy and frequently think of ending things. You hold out in hopes of returning to your time, but that day never comes. " ;
                    do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        break;
    case 4:
        cout<<"Insurgent:\"How dare you? Now you turn on us? Now of all times?\""<<endl<<endl<<"You run past the remaining soldiers. They give chase for a while but cannot compete with your agility. You make your way back to the town finding refuge in the bottom of the tower where it all began. Little do you know the place is completely overrun with insurgents. You may have been able to get away then, but this time the numbers overcome you. You quickly capture you and consfiscate the artifact. You are tied to a flag and your body is paraded throughout the city next to the General, Qazi and other former rulers.";
                    do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        break;
    }

}



int randomise() 
{                                                             //for attribute checks
    srand(time(0));
    roll = (rand() % 20) + 1;
    return roll;
}

void objectives(int i){
  switch (phase)
  {
  case 1: if (hint1 == true)
  {
    cout<<endl << "\"Why am I here?\""<<endl;
    cout<<endl << "Task: Find your purpose (hint: mosque)" << endl;
    UserMenu(i);
  }
  else 
   {
    cout<<endl << "\"Why am I here?\""<<endl;
    cout<<endl << "Task: Find your purpose" << endl;
    hint1 = true;
    UserMenu(i);
   }
  break;

  case 2:
     if(ownerkilled == false && CultInteraction==false && CoffeeOwnerInteraction == false)
     {
     cout<< endl << "\"The man in the tunnel trusted me with his task, should I do it?\""<<endl;
     cout<<endl<<"Task: Kill the coffeehouse owner if you want to help the cult" << endl;
     }
     else  if(ownerkilled == false && CoffeeOwnerInteraction == true)
     {
     cout<< endl << "\"What the hell was I thinking? The cult is not the way.\""<<endl;
     cout<<endl<<"Task: Find purpose elsewhere (hint: mosque)" << endl;
     }
     else if (ownerkilled == true && CultInteraction==true)
      {
      cout << endl << "\"What's done is done. I guess I'm in the espionage business now?\"" << endl;
      cout << endl << "Task: Go to the Citadel" << endl;
      }
     else
     {
      cout << endl << "\"It was for the greater good\"" << endl;
      cout << endl << "You have done the cult's bidding. You have a feeling the man will be back soon." << endl;
     }
    UserMenu(i);
    break;
  
  case 3:
    if(cult == true && CoffeeOwnerInteraction==false)
     {
     cout<< endl << "\"The man in the tunnel trusted me with his task, should I do it?\""<<endl;
     cout<<endl<<"Task: Kill the coffeehouse owner if you want to help the cult" << endl;
     }
     cout<<endl<<"\"The man in the Mosque mentioned a citadel\""<<endl;
     cout<<endl<<"Task: Travel to the citadel to uncover the truth"<<endl;
     UserMenu(i);
     break;

  case 4:
    cout<<endl << "\"Almost home\""<<endl;
    if (hint2 == true)
    {
    cout<<endl<<"Task: Seize the artifact using the cult or the caliphate. (hint: fort)"<<endl; 
    UserMenu(i);
    }
    else
    {
    cout<<endl<<"Task: Seize the artifact using the cult or the caliphate. (hint: fort)"<<endl; 
    hint2 = true;
    UserMenu(i);
    }
  break;

  default: 
    break;
  }
}

void lvl_up() {
    int stat;
  do{
    cout << endl << "You have leveled up, what would you would like to upgrade?" << endl;
    cout << "(1) Charisma" << endl << "(2) Strength" << endl << "(3) Intelligence" << endl;
    cin >> stat;
  } while (stat<1 && stat>3);
    switch (stat) {
        case 1:
            charism++;
            break;
        case 2:
            strength++;
            break;
        case 3:
            intel++;
            break;
        default:
            cout << endl << "Invalid" << endl;
            lvl_up();
            break;
    }
}

bool intel_check(int x) {
    int total;
    bool success = false;
    total = intel + randomise();
    cout << endl <<"You Needed: " << x ;
    cout << endl <<"You Rolled: " << total << endl<<endl;
    if (randomise() == 20)
    {
        cout << "Intelligence check passed" << endl << endl;
        success = true;
    }
   else if (randomise() == 1) {
        cout << "Intelligence check failed" << endl << endl;
        success = false;
    } 
    else
     {
        if (total >= x)
        {
         success = true;
         cout << "Intelligence check passed" << endl << endl;
        } else {
         success = false;
         cout << "Intelligence check failed" << endl;
        }
     }
    return success;
}

bool cha_check(int x) {
    int total;
    bool success = false;
    total = charism + randomise();
    cout << endl <<"You Needed: " << x ;
    cout << endl <<"You Rolled: " << total << endl<<endl;
    if (randomise() == 20)
     {
        cout << "Charisma check passed" << endl << endl;
        success = true;
     }
    else if (randomise() == 1) 
    {
        cout << "Charisma check failed" << endl<<endl;
        success = false;
    }
    else 
    {
        if (total >= x) {
            success = true;
            cout << "Charisma check passed" << endl << endl;
        } else {
            success = false;
            cout << "Charisma check failed" << endl << endl;
        }
     }
    return success;
}

bool str_check(int x) {
    int total;
    bool success = false;
    total = strength + randomise();
    cout << endl <<"You Needed: " << x ;
    cout << endl <<"You Rolled: " << total << endl<<endl;
    if (randomise() == 20)
     {
        cout << "Strength check passed" << endl<<endl;
        success = true;
     } 
    else if (randomise() == 1)
     {
        cout << "Strength check failed" << endl << endl;
        success = false;
     } 
     else
     {
        if (total >= x) {
            success = true;
            cout << "Strength check passed" << endl << endl;
        } else {
            success = false;
            cout << "Strength check failed" << endl << endl;
        }
     }
    return success;
}




void set_attr() {
    do {
        cout << "Enter your stats, totaling 10" << endl;
        cout << "Charisma: " << endl;
        cin >> charism;
        cout << "Intelligence: " << endl;
        cin >> intel;
        cout << "Strength: " << endl;
        cin >> strength;
    } while ((intel + strength + charism > 10) || (intel + strength + charism < 10));
}



bool cult_lead(){
cout<<"You continue through the tunnels.The air becomes tangibly dense. You begin to feel lightheaded."<<endl<<endl;
cout<<"\"Are you seeking purpose stranger?\""<<endl<<endl;
cout<<"You are able to make out a dark figure, standing out in distance. His voice soothes you until you finally give out to weariness."<<endl<<endl;
cout<<"You awake in a garden, filled with the most exotic of flora. A man with a grey beard awakes you and brings you to your feet. He guides to a large table adorned with silk cloth. He pours wine into a glass and hands it to you. You take a drink and grow weary yet again"<<endl<<endl;
cout<<"You see the same man waking you once again."<<endl<<endl;
cout<<"\"Awake now youth, if you want to return to heaven we have much to do.\""<<endl<<endl;
cout<<"He leads you to a dark and musty inner sanctum, and asks you to sit on a wooden chair."<<endl<<endl;
cout<<"\"Was that not the best experience you have had? Do you know why Adam was brought to Earth from Heaven? Sin. Sin is what limits us to this realm, filled with misery and pain and torture. So how do we get back to heaven? We must PURGE this society of sin. Help me help our people.\""<<endl<<endl;
    int choice;
    do{
    cout<<"(1) I'll join you"<<endl<<"(2) No"<<endl<<endl;
        cin>>choice;
    } while ((choice>2) || (choice<1));
    switch (choice)
    {
    case 1:
        cout<<"\"Alright then, let's get to work. First up on the agenda: The coffeehouse owner continues to bootleg alcohol, even after we...informed him, of the consequences. Show him those consequences."<<endl<<endl;
        phase++;
        lvl_up();
        cult=true;
        break;
    case 2:
        cout<<"\"Really? Not even after all that? You are exactly the kind of scum this society needs to be purged of. I can't just let you go.\""<<endl<<endl;
        cout<<"He lunges at you with his dagger"<<endl<<endl;
        if (str_check(18)==true)
        {
            cout<<"You overpower him and bring his insurgency to a quick end. You pick up his dagger and find 500 dinars in his pocket. You go back up the tunnel and go to sleep."<<endl<<endl;
            inventory_amount[1]+=1;
            wallet+=500;
        }
        else{
            cout<<"You are stabbed, and fall to the ground. He nods his head in disapproval as you bleed to death on the floor."<<endl<<endl;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
    break;
    }    
}


bool Qazi()
{
  string userin;
  int userint;
  cout << endl << "You now notice an inscription, in Arabic: \"The Judge's Residence\"." << endl;
  cout << endl << "\"Who are you? What are you doing at my house?\" " << endl;
  if (intel_check(20)==true)
   {
    cout << "(1) Use Intelligence" << endl;
        QaziInteraction=true;
   }
  if (str_check(30)==true)
   {
    cout << "(2) Use Strength" << endl;
        QaziInteraction=true;
   }
  if (cha_check(15)== true)
   {
    cout << "(3) Use Charisma" << endl;
    QaziInteraction=true;
   }
  if (wallet>500)
   {
    cout <<"(4) Bribe (500) " << endl;
   }
   if (strength <=4 && charism <=4 && intel <=4 && wallet <=500)
    {
        cout << endl << "You have nothing to say back. " << endl;
        return false;
    }
  cin >> userint;

  switch(userint)
   {
    case 1: cout << endl << "\"I have recently uncovered a plot against our city, a conspiracy that threatens to undermine the very foundations of our society. I believe you are the only one who can thwart it, but I dare not discuss such matters out in the open. May we step inside where we can speak freely?\"" << endl;
    break;
    case 3: cout << endl << "\"My intentions are noble. I find myself in need of a patron, someone of your esteemed stature, to guide me in my endeavors. I thought, what better way to seek your favor than to approach you directly? I seek only a few moments of your time, General, and the pleasure of sharing ideas with a brilliant mind such as yours. Allow me to prove the worth of our conversation.\"" << endl;
    break;
    case 2: cout << endl << "\"No time for formalities, Qazi. I bear news that requires your immediate attention. Step aside; we need to talk.\"" << endl;
            cout << endl << "The Qazi responds, annoyed: \"Who the hell do you think you are, barging into my home like this?\" " << endl;
            if (inventory_amount[1]>0)
             {
              cout << endl << "You have a dagger in your inventory. You draw it threateningly." << endl;
              cout << endl << "\"My business is urgent, Qazi, and I suggest you listen carefully. I don't want any trouble, but I won't be denied an audience with you.\"" << endl;   
             }
            else 
             {
                cout << endl << "You have no weapons in your inventory to intimidate the Qazi, do you try to fight him?" << endl;
                cin >> userin; 
                 if(userin == "yes")
                  {
                    cout << endl << "\"Bastard! You dare attack the Qazi of Damascus? You are a dead man walking. Guards!\"" << endl;
                    cout << endl << "You find yourself surrounded by a dozen armed guards. There is no way to fight them. You are jailed for the night. You wake up the next morning, teary-eyed, awaiting your execution." << endl;
                     dead =true;
                  }
                else
                 {
                    cout << endl <<"You back off." << endl;
                     QaziInteraction=true;
                    return false;
                 }
             }

    break;
    case 4: cout << endl << "\"Have you no respect for the honor of this house?\"" << endl;
            return false;
    break;

    default: Qazi();
   }
 if(userint==2)
 {
  cout << endl << "The Qazi reluctantly lets you into his house." << endl;
 }
 else
 {
  cout << endl << "The Qazi lets you into his house." << endl;
 }
  switch (userint)
   {
    case 1: cout << endl << "You make up a believable conspiracy on the spot, positing it with absolute conviction. The Qazi is impressed by your intelligence, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;
    case 2: cout << endl << "Despite your rudeness, The Qazi is impressed by your show of strength, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;
    case 3: cout << endl << "The Qazi is flattered, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;

    default: cout << endl << "You talk, but are unable to gain his favour. " << endl;
             QaziInteraction=true;
             return false;
   }

}

bool General()
{
  string userin;
  int userint;
  cout << endl << "You now notice an inscription, in Arabic: \"The General's Residence\"." << endl;
  cout << endl << "\"Who are you? What are you doing at my house?\" " << endl;
  if (intel_check(20)==true)
   {
    cout << "(1) Use Intelligence" << endl;
   }
  if (str_check(30)==true)
   {
    cout << "(2) Use Strength" << endl;
   }
  if (cha_check(15)==true)
   {
    cout << "(3) Use Charisma" << endl;
   }
  if (wallet>500)
   {
    cout <<"(4) Bribe (500) " << endl;
   }
   if (intel_check(20)==false && str_check(30)==false && cha_check(15)==false && wallet <=500)
    {
        cout << endl << "You have nothing to say back. " << endl;
        return false;
    }
  cin >> userint;

  switch(userint)
   {
    case 1: cout << endl << "\"I have recently uncovered a plot against our city, a conspiracy that threatens to undermine the very foundations of our society. I believe you are the only one who can thwart it, but I dare not discuss such matters out in the open. May we step inside where we can speak freely?\"" << endl;
    break;
    case 3: cout << endl << "\"General, my intentions are noble. I find myself in need of a patron, someone of your esteemed stature, to guide me in my endeavors. I thought, what better way to seek your favor than to approach you directly? I seek only a few moments of your time, General, and the pleasure of sharing ideas with a brilliant mind such as yours. Allow me to prove the worth of our conversation.\"" << endl;
    break;
    case 2: cout << endl << "\"No time for formalities, General. I bear news that requires your immediate attention. Step aside; we need to talk.\"" << endl;
            cout << endl << "The General responds, annoyed: \"Who the hell do you think you are, barging into my home like this?\" " << endl;
            if (inventory_amount[1]>0)
             {
              cout << endl << "You have a dagger in your inventory. You draw it threateningly." << endl;
              cout << endl << "\"My business is urgent, General, and I suggest you listen carefully. I don't want any trouble, but I won't be denied an audience with you.\"" << endl;   
             }
            else 
             {
                cout << endl << "You have no weapons in your inventory to intimidate the General, do you try to fight him?" << endl;
                cin >> userin; 
                 if(userin == "yes")
                  {
                    cout << endl << "\"Bastard! You dare attack the General of Damascus? You are a dead man walking. Guards!\"" << endl;
                    cout << endl << "You find yourself surrounded by a dozen armed guards. There is no way to fight them. You are jailed for the night. You wake up the next morning, teary-eyed, awaiting your execution." << endl;
                    dead =true;
                  }
                else
                 {
                    cout << endl <<"You back off." << endl;
                    return false;
                 }
             }

    break;
    case 4: cout << endl << "\"Have you no respect for the honor of this house?\"" << endl;
            return false;
    break;

    default: General();
   }
 if(userint==2)
 {
  cout << endl << "The General reluctantly lets you into his house." << endl;
 }
 else
 {
  cout << endl << "The General lets you into his house." << endl;
 }
  switch (userint)
   {
    case 1: cout << endl << "You make up a believable conspiracy on the spot, positing it with absolute conviction. The General is impressed by your intelligence, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;
    case 2: cout << endl << "Despite your rudeness, The General is impressed by your show of strength, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;
    case 3: cout << endl << "The General is flattered, you have gained favour with him. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
    return true;
    break;

    default: cout << endl << "You talk, but are unable to gain his favour. Seeing this, you ask him about the artefact. He tells you it is being kept at the fort under heavy security." << endl;
            return false;
   }

}

void Sultan()
{
  string userin;
  cout << endl << "You approach the Sultan. He looks worried, the weight of the crown seems to have worn him down. He seems busy, do you initiate the conversation? " << endl;
  cin >> userin;
  if(userin=="yes")
   {
      if (sultanoffense==false)
       {
        cout << endl << "\"Why is this stranger speaking to me out of turn? Who let him in?\"" << endl;
        cout << endl << "It seems you have offended the Sultan. You can try again, but he is unlikely to grant you any favours. " << endl;
        sultanoffense = true;
        Palace();
       }
     else 
      {
        cout << endl << "\"La Hawla Wala Quwwata, you again! Do you not learn?\"" << endl;
        cout << endl << "You have angered the Sultan and are promptly kicked out of the Palace. " << endl;
        UserMenu(0);
      }
   }
  else if (userin == "no" && sultaninteraction == false)
  {
    int userint;
    cout << endl << "You sit and wait quietly for the Sultan to tend to his affairs. A few hours later, he addresses you:" << endl;
    cout << endl << "\"Ah, the foreigner. The " << palref << " seems to really like you. He said you give good advice. So, what do you have to say to me?\"" << endl;

    cout << endl << "(1) Use Intelligence" << endl;
    cout << "(2) Use Charisma" << endl;
    cout << "(3) Use Strength" << endl;
    cin >> userint;

    if(userint == 1 && intel_check(15)==true)
     {
        cout << endl << "\"Your Eminence, while charisma may sway the hearts, intelligence shall navigate the path ahead. Our decisions must be calculated, grounded in foresight and wisdom. Let us not only defend our realm but outsmart those who plot against us, ensuring the longevity of our legacy.\"" << endl;
        cout << endl << "The Sultan is impressed, and offers you a position on his advisory council. You would have to abandon your quest, but are guaranteed power and riches for life. Do you accept? " << endl;
          cin>> userin;
           if(userin == "yes")
            {
                cout << endl << "You live the rest of your life as an advisor to the Sultan. You live a comfortable life, but regret not trying to return to your time; You miss the internet, you miss fast food, and you miss your friends everyday till you grow so old you forget what you are or where you came from." << endl;
                            do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
            }
           if (userin == "no")
            {
             cout << endl << "He respects your decision. You are awarded 3000 dinar to help in your calling." << endl;
             wallet +=3000;
             sultaninteraction = true;
             Palace();
            }
     }
    else if (userint ==2 && cha_check(15)==true)
    {
        cout << endl << "\"Majesty, our people long for a leader who captures their hearts, a Sultan whose words resonate like poetry. Engage with them, share in their joys and sorrows. Let them feel your warmth, and they will follow you not out of fear, but out of admiration and love. You are a storyteller, a symbol, a source of inspiration. In your charisma, they will find the fire that lights the path forward.\"" << endl;
         cout << endl << "The Sultan is flattered, and offers you a position as foreign ambassador on behalf of the Caliphate. You would have to abandon your quest, but get to travel the ancient world and see all the wonders lost to history. Do you accept? " << endl;
          cin>> userin;
           if(userin == "yes")
            {
                cout << endl << "You live the rest of your life as the foreign ambassador to the Franks. You live an eventful life, but regret not trying to return to your time; You miss the internet, you miss fast food, and you miss your friends everyday till you grow so old you forget what you are or where you came from." << endl;
                            do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
            }
           if (userin == "no")
            {
             cout << endl << "He respects your decision. You are awarded 3000 dinar to help in your calling." << endl;
             wallet +=3000;
            sultaninteraction = true;
             Palace();
            }
    }
    else if (userint == 3 && str_check(15)==true)
     {
        if (intel_check(5)==true)
         { 
         cout << endl << "\"Your Excellency, the winds of treachery blow through the corridors of power. Our enemies lurk in the shadows, eager to exploit any crack in our foundation. We must forge a realm of unyielding might, crush dissent with an iron fist, and make them tremble at the mere thought of crossing the Caliphate.\"" << endl;
         cout << endl << "The Sultan is impressed, and offers you a high-ranking position in the Caliphate's army. You would have to abandon your quest, but are guaranteed power and riches for life. Do you accept? " << endl;
          cin>> userin;
           if(userin == "yes")
            {
                cout << endl << "You live the rest of your life as a high-ranking officer in the Abbassid army. You live an adventurous life, but regret not trying to return to your time; You miss the internet, you miss fast food, and you miss your friends everyday till you die in battle a middle-aged man." << endl;
                            do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
            }
           if (userin == "no")
            {
             cout << endl << "He respects your decision. You are awarded 3000 dinar to help in your calling." << endl;
             wallet +=3000;
            sultaninteraction = true;
             Palace();
            }
         }
        else 
         {
            cout << endl << "\"Your Excellency, the throne upon which you sit is not immune to the currents of discontent that swirl within our court. There are whispers, murmurs that question the strength of your rule. Do not dismiss them lightly.\"" << endl;
            cout << endl << "You speak with strength and conviction, but lack the finnesse to do it without offending the Sultan; He takes your words as a challenge to his authority, and immediately orders you killed. You are arrested and spend the night in jail. You are violently woken up the next day to be executed by sword. " << endl;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
         }
     }
     else if (intel_check(15)==false && str_check(15)==false && cha_check(15)==false)
     {
      cout << endl << "You realize you have nothing to say. You stare at the Sultan blankly, and without saying a word, walk out of the Palace in shame. The Sultan and his court is confused by this, but ultimately unfazed. " << endl;
      UserMenu(0);
     }
    else 
    {
        Palace();
    }






  }
  else if (userin == "no" && sultaninteraction == true)
  {
    cout << endl << "You have already had a private audience with the Sultan. He cannot give you any more of his time. " << endl;
    Palace();
  }
  else 
  {
    Palace();
  }
}

bool trial3(){
    bool death =false;
    cout<<"There it is. Right ahead of you. Upon it's own throne. The artifact awaits you. "<<endl<<endl;
    if (intel_check(9)==true){
        cout<<"You detect the trip-activated spikes ahead and jump over."<<endl<<endl;
        return death;        
    }
    else{
        cout<<"You run towards the artifact, this item has never been closer to you or your cause. Until... you feel the sensation of a light wire against your foot. Spikes impale you."<<endl<<endl;
        death=true;
        return death;        
    }
}

bool trial2(){
    int choice;
    bool death =false;
    do{
    cout<<"You advance forth."<<endl<< "\"Hey are you one of us? Grand-Master told me you would be arriving soon.\""<<endl<<endl;
    cout<<"(1) Yep that's me"<<endl<<"(2) Wait, Grandmaster, are you an insurgent?"<<endl<<endl;
    cin>>choice;
    } while ((choice>2) || (choice<1));;
    switch(choice)
        {
        case 1:
        cout<<"He lunges at you and stabs you straight through the heart."<<endl<<endl<<"\"We rooted out your little double agent before. Even then, what did you expect? Do you just openly declare alligances? Is this the best you have to offer?\""<<endl<<endl<<"You die of embarassment... and the fatal wound through the heart."<<endl<<endl;
        death=true;
        break;

        case 2:
        cout<<"No no no, wait, I was just checking for any stealth rebels."<<endl<<endl;
        cout<<"You go forth, with your head held up high."<<endl<<endl;
        death=false;
        trial3();
         if (trial3()==false){
                    cout<<"You have the artifact"<<endl<<endl;
                    endings(3);
                }
                else{
                    cout<<"You are dead."<<endl<<endl;
                }
        break;
    }
    return death;
}
bool trial1(int x){
    bool death = false;
    switch (x)
        {
        case 1:
        if (str_check(25)==true){
            cout<<"You are able to overpower them and make your way through"<<endl<<endl;
            trial2();
        }
        else{
            death=true;
        }
        return death;
        break;
        
        case 2:
        if (cha_check(25)==true)
        {
            cout<<"You are able to convince them that you are authorised to pass through"<<endl<<endl;
            trial2();
        }
        else{
            cout<<"They don't buy it and choose to skewer you"<<endl<<endl;
            death=true;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
        return death;
            break;
        case 3:
        cout<<"You surrender. They take you as a hostage, and torture you."<<endl<<endl<<"What did you expect?"<<endl<<endl;
        return death;
        break;
        }      
}
void cult_2(){
    int choice;
    char cont;
    do {
    cout <<endl<< "Press x to continue" << endl;
    cin>>cont;
    } while (cont != 'x');
    
    cout<<"You awake the next day in the tunnel you started from. "<<endl<<endl;
    cout<<"\"Did you do it?\""<<endl<<endl;
    cout<<"You hear the voice of the man, and reply in the affirmative."<<endl<<endl;
    cout<<"\"Excellent. Now that you have proven yourself, we can move onto more pressing matters; First, an introduction, our organisation formed under the worst of circumstances. The caliphate has chosen to establish a degenrate order over us. Day by day more of Islam is violated by these heathens to enable themselves. Do their mansions of gold, their gated society using the public treasury represent the sanctity of Islam? The rule of the first four Caliphs? They have thus let go of any claim to authority they had.\""<<endl<<endl;
    cout<<"\"This is not Abu Bakr's rule, nor Umar or Usman or Ali. What we are doing is justified resistance.\""<<endl<<endl; 
    cout<<"\"According to one of our spies in the citadel, the government recently found an artifact. This artifact cause a tear in the sky. This is the answer to our prayers. This is how God enables us to bring justics to this land again.\""<<endl<<endl;
    cout << "\"They may have the artifact, but they do not know how to use it. One of our mystics, through divine inspiration, anticipated its arrival. He says the relic can bend time, and must not fall into the wrong hands.\"" << endl << endl;
    do{
    cout<<"\"Now, you have two choices.\""<<endl<<endl<<"An old woman dressed in black hobbles out of the shadows. She holds a large staff adorned with bone articrafts. She is visibly dying. Each gasp of air she takes produces audible uneasiness."<<endl<<endl;
    cout<<"The man continues.\"That there is an elderly sister of the group. God has blessed her with the ability to move things. Unfortunately her frail body cannot do this much longer. She wills to be martyred for the cause. She will achieve her goal helping us achieve our goal. She can send you directly to the fort so that you may bring the artifact to those God intended for it to be held by. However this endeavor will be quite challenging, or you can go to the citadel itself as our spy and steal it from there. What do you say?\""<<endl<<endl;
    cout<<"(1) I'll do it"<<endl<< "(2) I'd rather be a double-agent"<<endl<<endl;
    cin>>choice;
    } while ((choice>2) || (choice<1));
    switch (choice)
    {
    case 1:
        cout<<"\"Thank you\""<<"The woman stammers. She finds an empty spot in the room, raises her staff and summons a portal."<<endl<<endl;
        cout<<"You make your way through the portal."<<endl<<endl<<"You are now in the fort."<<endl<<endl;
        do{
        cout<<"Before you are two guards. They have not yet seen you."<<endl<<endl;
        cout<<"(1) Attack them head on (Strength)"<<endl<<endl<<"(2) Talk your way past them (Charisma)"<<endl<<endl<<"(3) Surrender"<<endl<<endl; 
        cin>>choice;
        }while ((choice>3) || (choice<1));
        if (trial1(choice)==true){
            cout<<"You are dead."<<endl<<endl;
        }
        break;

    case 2:
        cout<<"The old woman looks disappointed and disappears back into the dark."<<endl<<endl;
        cout<<"\"Very well, make your way to the citadel and save us.\""<<endl<<endl;
        CultInteraction = true;
        break;
    }
}

void Scholar()                    
{
  string userin;
  bool boolcha = cha_check(8);
  cout << endl << "You approach the scholar. He sizes you up, but does not initiate a conversation. You want to say something, but are mystified. Do you try to speak? " << endl;
  cin >> userin;

if(userin == "yes" || userin == "Yes")

    if (intel_check(25)==true)
     {
        string userin;
        cout << endl << "You immediately start talking to him about contemporary art and science. He is blown away by your knowledge. He sees potential in you, and offers you an apprenticeship. You would have to devote your life to academia and cannot go back to your home. However, you are guaranteed financial security for a lifetime and maybe even a place in the history books. Do you accept? " << endl;
        cin>>userin;
        if (userin == "yes" || userin == "Yes")
         {
          cout << endl << "You live the rest of your life as an assistant to the scholar. You live a comfortable life and you learn a lot, but regret not trying to return to your time; You miss the internet, you miss fast food, and you miss your friends everyday till you grow so old you forget what you are or where you came from." << endl;
                      do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;

         }
        else 
         {
            cout << endl << "He respects your decision. He hands you a flat, circular disc, its surface adorned with intricate engravings that, in his words:" << endl;
            cout << endl << "\"Tell tales of the stars; A central pivot point allows the alidade, a slender arm, to gracefully rotate, serving as the instrument's guiding hand in the dance of the cosmos. The astronomer then delicately aligns the alidade, its gaze fixed on the celestial wonders that shimmer overhead.\" " << endl;
            cout << endl << "This device, you are told, is an astrolabe. It is worth 2000 dinar. " << endl;
            scholarinteraction = true;
            wallet += 2000;
            Palace();
         }
     }
    else if(intel_check(8)==false && boolcha ==false)
      {
        cout << endl << "As soon as you start speaking, he starts dozing off. You are not charismatic or intelligent enough to hold his attention, and have nothing interesting to say. " << endl;
        scholarinteraction = true;
        Palace();
       }
    else if (intel_check(20)==true && boolcha ==false)
     {
        cout << endl << "You struggle to keep him engaged in the conversation, but he is impressed by your intelligence. He can tell you are not from here, and gives you tips on how to be more likeable in Damascene culture. " << endl;
        cout << endl<< "\"Lower your voice, speak softly. Do not stare. Always greet people warmly.\"" << endl;
        cout << endl <<"You start paying more attention to how you carry yourself. This boosts your charisma. " << endl;
        charism++;
        scholarinteraction = true;
        Palace();
     }
    else if (cha_check(15)==true)
     {
        cout << endl << "He enjoys your conversation and hands you a book to read. " << endl << "This has been added to your inventory." << endl;
        inventory_amount[5] += 1;
        intel++;
        scholarinteraction = true;
        Palace();
     }
    else 
     {
        cout << endl<< "You have a very enlightening conversation. He can tell you are not from around here, and tells you all about Damascene culture and society. You come out of the conversation a much smarter man. " << endl;
        intel+=4;
        scholarinteraction = true;
        Palace();
     }
  else
   {
     Palace();
   }
}


void Palace()
{

    UserMenu(2);
    int userint;
    if (scholarinteraction == true && sultaninteraction == true)
     {
        cout << endl << "You have done all you came here to do. You are respectfully escorted out of the palace by armed guards." << endl;
        UserMenu(0);
     }
    cout << endl <<"The grand entrance, adorned with intricate geometric patterns and calligraphy, serves as a prelude to the majestic realm beyond. The air is laden with the scent of blossoms, and the gentle sound of water trickling from fountains creates a serene ambiance within the palace courtyard." << endl;
    cout << endl << "As you cross the gates, you are welcomed by architectural splendor that defines the essence of the Abbasid era. The interiors boast soaring arches, vaulted ceilings, and meticulously crafted domes. Marble floors and intricately carved designs adorn every surface, reflecting the rich artistic heritage of Islamic culture. Luxurious furnishings, large carpets, and vibrant textiles command even more regality as the Sultan's guards invitingly let you into the heart of the palace, courtesy of the " << palref << "'s reference. " << endl;
    cout << endl <<"Finally, you see the Sultan on his throne. Next to him, his advisor, who happens to be a very famous scholar. It is said that a single conversation with the man can change people. " << endl;
    cout << endl <<"(1) Approach the Sultan" << endl << "(2) Approach the Scholar" << endl;
    cin >> userint;

    if(userint == 1)
     {
     if(sultaninteraction == false)
      {
       Sultan();
      }
      else
      {
       cout << endl << "You have already had a private audience with the Sultan. He cannot give you any more of his time. " << endl;
        Palace();
      }

     }
    else if (userint == 2)
    {
      if(scholarinteraction == false)
      {
       Scholar();
      }
      else
      {
        cout << endl << "You already spoke with the Scholar, you have nothing more to say." << endl;
        Palace();
      }

    }
    
    else
     {
       Palace();
     }

}

void CitadelGuardsDialogue()
{
  int userint;
  string userin;
  bool access = false;
  bool boolstrength = str_check(20);
  cout << endl << "You approach the guards. They do not react to your presence. " << endl;
  cout << endl << "(1) Use Strength" ;
  cout << endl << "(2) Use Charisma " ;
  cout << endl << "(3) Use Intelligence ";
  if (wallet>1000)
  cout << endl << "(4) Bribe (1000)";

  if (intel_check(15)==false && cha_check(15)==false && boolstrength==false && wallet <=1000)
     {
        cout << endl << "You cannot think of a way to get their attention. Do you try and fight them? " << endl;
        cin>>userin;
        if(userin == "yes" && boolstrength==true)
         {
           cout << endl << "The guards put up a valiant effort, but ultimately lose." << endl;
           if(inventory_amount[1]>0)
           { cout << endl << "You have a dagger in your inventory." << endl;
            cout << endl << "(1) Kill and loot one of them" << endl << "(2) Proceed towards the Citadel" << endl;
            cout << "(Note: Killing will remove one dagger from your inventory)" << endl;
            cin >> userint;
            if (userint == 1)
             {
              cout << endl << "You pull out your dagger and eye one of the guards. As you walk towards him, the guard grovels at your feet, begging you not to do it. He offers you 200 dinar, claiming it is all he has. You can hear him sobbing and reciting a prayer. Do you take pity?" << endl;
              cin >> userin;
                if(userin == "no")
                 {
                   cout << endl << "You stab him three times and leave him a bloody mess. It takes 10 long minutes for him to finally give out. You find 200 dinar and some bread in his pocket. " << endl;
                   inventory_amount[1] -=1;
                   wallet +=200;
                   inventory_amount[3] +=2;
                   Citadelin();
                 }
                else 
                 {
                  cout << endl << "You have mercy and accept the 200 dinar." << endl;
                  wallet+=200; 
                  Citadelin();
                 }
             }
            else
              { Citadelin();} 
          }
         }
        else if (userin == "yes" && boolstrength==false)
         {
            cout << endl << "Desperate, you try to fight your way in. One of the guards picks you up and throws you against the wall, warning you not to be a nuisance." << endl;
              if (intel_check(6)==true)
               {
                cout << endl << "You pay heed to this warning and peacefully leave the Citadel without any injury or harm done. " << endl;
                UserMenu(0);
               }
              else 
               {
               cout << endl << "Not knowing any better, you try to get up and confront them again. You are promptly thrown back onto the pavement. Annoyed, the other guards join in and kick you until your body goes limp. You lie there on the ground for hours while life continues as usual around you, people entering and leaving the gate glare at you throughout the day. Embarrassed, you crawl away from the citadel and back onto the streets. " << endl;
               cout << endl << "Not only are you weakened, but being seen in such a pathetic state gets you negative attention. This affects your charisma. " << endl;
               strength = strength - 2;
               charism = charism-2;
               UserMenu(0);
               }
              
         }
        else 
         {
            cout << endl << "You leave the Citadel. " << endl;
            UserMenu(0);
         }
     }
    cout << endl;
    cin >> userint;

    if (userint ==1 && str_check(20)==true)
     {
       cout << endl <<"With an air of authority, you fix a stern gaze upon the guards. Your voice, low and commanding, carries a subtle threat:" << endl;
       cout << endl << "\"I strongly advise you to consider the consequences of denying me passage. The matters I attend to are not to be trifled with. Grant me access, and you shall remain unharmed in the shadows of my endeavors.\"" << endl;
       access =true;
     }
    else if (userint == 2 && cha_check(10)==true)
    {
      cout << endl << "With a smile, you engage the guards:" << endl ;
       cout << endl << "\"Gentlemen, I wish to document the lifestyles of the rich in this city. I write history for a living, imagine the tales that I could tell of your benevolence, if only you permit me through this gate! Or would you rather be forgotten to time?\""<< endl;
        access =true;
    }
    else if (userint == 3 && intel_check(10)==true)
    {
     cout << endl <<"With a thoughtful expression, you appeal to the guards:" << endl;
     cout << endl << "\"Wise guardians, I approach with a humble request. The matters I pursue on the other side are intricately tied to the well-being of this great city. Permit me through, and I shall share the knowledge that awaits, ensuring the continued prosperity of Damascus.\"" << endl;
      access =true;

    }
    else if (userint == 4 && wallet>1000)
    {
      cout << endl << "With a sly grin, you discreetly produce a small pouch filled with coins. Your voice, smooth and conspirational, suggests:" << endl;
      cout << endl << "\"I believe every loyal guardian deserves a token of appreciation. Allow me through this gate, and these dinar could find a new home in your pockets. Consider it a gesture of gratitude for your understanding in this matter.\"" << endl;
      access=true;
      wallet -= 1000;
      
    }
    else 
    {
        cout << endl << "You try to speak, but slur your words. The guards look at you, confused. You hurriedly leave the Citadel in shame." << endl; 
        UserMenu(0);
    }
  
  if (access == true)
   {
    cout << endl << "The guards are convinced. You are let into the Citadel." << endl;
    Citadelin();
   }
}

void Djinn()
{
    int userin;
    cout << endl << "A force compels you to leave the mosque immediately. You go outside, a smoky mist rises from the ground and engulfs you, isolating you from the surroundings. A deep, low voice echoes through your head: " << endl;
    cout << endl << "\"As the moon whispers secrets to the night, mortal, your wishes may dance with delight, but every desire kindles a shadowy debt, and as fate intertwines, our conversation has just begun.\"" << endl;
    cout << endl << "It seems you have come across a Djinn. How do you respond? " << endl;

    if(str_check(15)==true)
    cout << endl << "(1) Strength" ;
    if(cha_check(15)==true) 
    cout << endl << "(2) Charisma " ;
    if (intel_check(15)==true)
    cout << endl << "(3) Intelligence ";
    if (wallet>10)
    cout << endl << "(4) Bribe (10) ";
    if (str_check(15)==false && intel_check(15)==false && cha_check(15)==false && wallet <=10)
     {
        cout << endl << "You cannot think of anything to say. The mist vanishes, as suddenly as it had appeared, and you find yourself on a random Damascene street." << endl;
        UserMenu(0);
     }
    cout << endl;
    cin >> userin;

    if (userin ==1)
     {
       cout << endl <<"\"Your ominous words may send shivers, but I won't cower in fear. If there's a price to pay, I'll face it head-on, for I shape my destiny.\"" << endl;
       DjinnInteraction = true;
     }
    else if (userin == 2 )
    {
      cout << endl << "\"Celestial maestro, your words weave a captivating melody. If a dance with destiny awaits, let's twirl through the shadows together, for in the steps of curiosity, perhaps we'll discover the harmony between wishes and the debts they entail.\"" << endl;
      DjinnInteraction = true;
    }
    else if (userin == 3)
    {
     cout << endl <<"\"In this convoluted tapestry of wishes and consequences, your aspirations unfold like a delicate theorem: each wish a variable in the equation of fate. May your calculations be astute, and the solutions discovered within the labyrinth of existence lead you to the harmonious equilibrium sought by every seeker of the cosmic unknown.\"" << endl;
     DjinnInteraction = true;

    }
    else if (userin == 4)
    {
      cout << endl << "\"Your material trinkets hold no allure for me.\"" << endl;
      cout << endl << "\"Besides, 10 dinar? Really? That's the best you could do?\"" << endl;
      cout << "The Djinn leaves unimpressed. The mist vanishes, as suddenly as it had appeared, and you find yourself on a random Damascene street." << endl;
      UserMenu(0);
    }
    else 
    {
        cout << endl << "You try to speak, but slur your words. The Djinn leaves unimpressed. The mist vanishes, as suddenly as it had appeared, and you find yourself on a random Damascene street." << endl; 
        UserMenu(0);
    }
   cout << endl << endl;
    if(DjinnInteraction == true)
     {
        cout << endl << "The Djinn materializes as a middle-aged man in a flowing white thobe adorned with intricate embroidery. He greets you with a warm smile." << endl << endl << "\"You seem worthy.\" " <<endl << endl << "He whispers something into your ear. You do not know what it means, you do not understand a single word, but it implants itself in your memory. " << endl;
        artkno = true;
        UserMenu(0);
     }
  
}

void MosqueMan(){                                                                                       //mosqueman, man at mosque
    int pick;
    cout<<endl <<"It is sparsely populated. "<<endl;
    cout<<endl <<"\"You're late for prayer\", says a man in rags. It is quite apparent that the mosque is his only abode."<<endl;
    do{
    cout<<"------------------------------------------------"<<endl;
    cout<<"(1) \"Who are you?\""<<endl<<"(2) \"Do you just live here?\""<<endl;
    cin>>pick; 
    } while (pick != 1 && pick !=2);
    switch (pick)
    {
    case 1:
       cout<<endl <<"\"Who I am does not matter; Who are you, traveller?\""<<endl;
        break;
    
    case 2:
    cout<<endl <<"\"You got a problem with it?\"" << endl;
        break;
    }
  do
    {
    cout<< endl << "You ask him about current affairs" << endl;  
    cout<<endl <<"\"Well, I am somewhat hungry\""<<endl;  
    cout<<endl <<"(1) \"So am I. Don't you think we should split information too?\""<<endl<<"(2) Beat the information out of him"<<endl<<"(3) \"...Fine\" Bribe (40)" <<endl<<"(4) \"Guess I'll just live without it\"" << endl;

        cin>>pick;
    } while ((pick>4) || (pick<1));
    switch (pick)
    {
    case 1:
        if (cha_check(15)==true){
            cout<<endl <<"Well, all I know is that the Sultan found an ancient artifact that split the sky in our town in an excavation. Came around yesterday. Only the Sultan's General or the Qazi would know more, and they live in the gated Citadel. No one else knows anything about it."<<endl;
            if(cult == true)
             {
              phase++;
              lvl_up();
                  MosqueManInteraction=true;
             }
            else
             {
              phase= phase+2;
              lvl_up();
                  MosqueManInteraction=true;
             }
            Mosque();
              
        }
        else
        {
            cout<<endl<<"Yeah? That's really dumb. Don't bother me if you don't have what I want."<<endl;
              Mosque();
        }
        break;
    case 2:
        if (str_check(15)==true)
        {
            cout<<endl<<"WAIT, WAIT STOP. Look, all I know is that the Sultan found an ancient artifact that split the sky in our town in an excavation. Came around yesterday. Only the Sultan's General or the Qazi would know more, and they live in the gated Citadel. No one else knows anything about it."<<endl;        
               MosqueManInteraction=true;
            if(cult == true)
             {
              phase++;
              lvl_up();
                  MosqueManInteraction=true;
             }
            else
             {
              phase= phase+2;
              lvl_up();
                  MosqueManInteraction=true;
             }
                           Mosque();
}
        else
        {
            cout<<endl <<"\"You really tried that in a mosque? Have you no class?\""<<endl;
            cout<<endl <<"He leaves you a bloody mess"<<endl;
                MosqueManInteraction=true;
                        Mosque();
        }
        break;
    case 3:
        if (wallet>40){
            wallet-=40;
            cout<<endl <<"Well, all I know is that the Sultan found an ancient artifact that split the sky in our town in an excavation. Came around yesterday. Only the Sultan's General or the Qazi would know more, and they live in the gated Citadel. No one else knows anything about it."<<endl;
            if(cult == true)
             {
               phase++;
               lvl_up();
                  MosqueManInteraction=true;
             }
            else
             {
              phase= phase+2;
              lvl_up();
                  MosqueManInteraction=true;
             }
              Mosque();
        }
        else
        {
            cout<<endl<<"\"No money, no information.\""<<endl;
                MosqueManInteraction=true;
                        Mosque();
        }
        break;
    case 4:
        cout<<endl<<"\"Get out of my face\""<<endl;
                    Mosque();
        break;            
    }
    MosqueManInteraction=true;
}

void Market()
{
  UserMenu(4);
  cout << endl << "As you step into the Bazaar, you are welcomed by narrow cobblestone alleys lined with makeshift stalls and tents showcasing vibrant textiles, ornate lanterns, and richly colored rugs. Skilled blacksmiths craft intricate metalwork, creating Damascus steel patterns. The marketplace is a kaleidoscope of colors with ceramics, jewelry, and spices neatly arranged. It captivates you, offering a glimpse into the city's rich cultural heritage." << endl;
  market_init(4);
}

void display_market_b() {
    for (int i = 0; i < 6; i++) {
        cout << i + 1 << "- Product: " << market_inventory_type[i] << endl << " Cost: " << price_[i] << endl;
    }
}

bool purchase_valid_b(int x) {
    bool valid = false;
    bool amount = false;
    bool cost = false;
    if (wallet > price_[x]) {
        cost = true;
    }
    if (market_inventory_capacity[x] > 0) {
        amount = true;
    }
    if (amount == true && cost == true) {
        valid = true;
        market_inventory_capacity[x] -= 1;
        wallet = wallet - price_[x];
        market_fund = market_fund + price_[x];
        inventory_amount[x]=inventory_amount[x]+1;
    } else {
        if (cost == false) {
            cout << endl << "\"You want to buy that? With what money?\"" << endl;
            Market();
        }
        if (amount == false) {
            cout << endl << "\"Sorry to disappoint, brother. I do not have any more of that item.\" " << endl;
            Market();
        }
    }
    return valid;
}


void buying() {
    int pick;
    cout << endl <<"\"Well, here's what I got: \""<<endl;
    display_market_b();
    do {
        cout << endl << "Enter the line number associated with your desired product for purchase: ";
        cin >> pick;
        if (pick < 1 || pick > 6) {
            cout << endl << "Invalid" << endl;
        }
    } while (pick < 1 || pick > 6);

    if (purchase_valid_b(pick - 1) == true) {
        cout << endl << "Purchase successful"<<endl;
        Market();

    }
}

bool purchase_valid_s(int x) {
    bool valid = false;
    bool amount = false;
    bool cost = false;
    if (market_fund > price_[x]) {
        cost = true;
    }
    if (inventory_amount[x] > 0) {
        amount = true;
    }
    if (amount == true && cost == true) {
        valid = true;
        inventory_amount[x] -= 1;
        market_fund = market_fund - price_[x];
        wallet= wallet+price_[x];
    } else {
        if (cost == false) {
            cout << endl <<"\"I don't have enough money.\"" << endl;
        }
        if (amount == false) {
            cout << endl << "\"Do I really look that dumb, habibi?\"" << endl;
            Market();
        }
    }
    return valid;
}

void display_inventory(int j) {
   for (int i = 0; i < 6; i++)
  {
  cout<<i+1<<": Product: "<<inventory_type[i]<<" Amount: "<<inventory_amount[i]<<endl; 
  } 
  cout << endl << "You have " << wallet << " dinar to your name." << endl;
  UserMenu(j);
}

void selling(int j) {
    int pick;
    cout << endl<< "\"What do you want to sell?\"" << endl;
    for (int i = 0; i < 6; i++)
  {
  cout<<i+1<<": Product: "<<inventory_type[i]<<" Amount: "<<inventory_amount[i]<<endl; 
  } 
    do {
        cout << endl<< "Enter the line number associated with your desired product for transaction: ";
        cin >> pick;
        if (pick < 1 || pick > 6) {
            cout << endl << "Invalid" << endl;
        }
    } while (pick < 1 || pick > 6);

    if (purchase_valid_s(pick - 1) == true) {
        cout << endl << "Transaction successful"<<endl;
        Market();
    }
}

void market_init(int j) {
    int pick;
    cout << endl<< "\"Welcome my friend. What brings you to my corner?\" " << endl;
    cout <<endl << "(1) Buy" << endl << "(2) Sell" << endl << "(3) Leave" << endl;
    cin >> pick;
    switch (pick) {
        case 1:
            buying();
            break;
        case 2:
            selling(j);
            break;
        case 3: 
             UserMenu(0);
        break;
        default:
            cout << endl <<"Invalid"<<endl;
            market_init(j);
            break;
    }
}

void Search(int j, int r)                                                      // location and risk as parameters
{
   srand(time(0));
                                                                                     
    int risk;
    int act;
    int i=0;         
    risk = rand() % r + 1 ;                                                            // r= risk variable, varies risk.the higher the riskier, hardcoded each location. also affects bail in prison.                                                                                  
    act = rand() % 20 + 1;
    bool a,b,c,d,e;
    bool itemflags[5] = {a,b,c,d,e};                                         //whether item present at location
    bool itemfound;

    const int probabilities[6] = {3,1,1,5,0,2};                                         // Adjusted probabilities for each item at location


    bool caught =false;                                                //state of being caught (possiblity,varies with location)
    const  int inum = 6;                                        //total number of collectible items in the game. 5 arbitrary.                                        
    string dag= "dagger", bread = "bread", cloth = "cloth" , coin = "coin" , astro = "astrolabe",book="book";
    string items[6] = {cloth,dag,"poison",bread,astro,book};                                //items present at a location
                                    

  if(act>risk)
    {
        caught = false;                                                        //not intuitive, but helps with bail in Prison();
    }
    else 
    {
        caught = true;
    }
    int p;
   for (i;i<inum;i++)
    {
      itemflags[i] = (rand() % 10 < probabilities[i]);                            // probabilities to set the presence of the item

      if (itemflags[i] == true)
       {
        cout <<endl<<"You find a " << items[i] << " when searching the " << loc[j] << "." << endl;
        cout <<"It has been added to your inventory." << endl ;
        inventory_amount[i] += 1 ;  
        p=i;   
        itemfound = 1;
        break;     
       }
    }
    
    if(!itemfound)
    {
        cout << endl<< "You find nothing of use" << endl;
    }
    if ((caught == 1 && strength<=5) || i==2 || i==3 )
    {
        cout <<endl << "You are caught trying to search the " << loc[j] << " and are unable to resist arrest."<< endl;
        if(itemfound == true)
         { cout << endl << "The " << items[p] << " you stole is confiscated. " << endl;
          inventory_amount[i] -= 1;
         }
        if (j==2 || j==3)
         { 
         cout << endl << "Since you tried to steal directly from the Caliphate, one of your hands is permanently maimed. Your strength is halved. " << endl;
         strength = (strength/2);
         }
       Prison(r);
    }
    else if (caught == 1 && strength>5 && i!=2 && i!=3)
    {
        cout << endl << "You are caught trying to search the " << loc[j] << " ." <<endl;
        cout << endl<<"You manage to fight your way out and avoid prison, but you lose some strength." << endl;
        strength --;
        UserMenu(j);
    }
   else 
    {
        cout << endl <<"You look around, no one saw you. " << endl;
        UserMenu(j);
    }
}

int cult_choice(){
    int choice;
    cout<<"\"Well done, now, hand it over.\""<<endl<<endl;
    do
    {
        cout<<"(1) Hand it over"<<endl<<"(2) Keep it"<<endl;
        cin>>choice;
    } while ((choice>2)||(choice<1));
    switch (choice)
    {
    case 1:
        endings(3);
        break;
    
    case 2:
        endings(4);
        break;
    }
    
}

void Fort()
{
    UserMenu(3);
    int choice; 
    cout<<endl << "The Damascene fort rose from the arid landscape like a colossal sentinel of time, a testament to the grandeur of ancient civilizations. Its massive stone walls, weathered by centuries of history, towered defiantly against the azure sky, casting imposing shadows that seemed to stretch for miles. As the sun dipped below the horizon, the fortress became an ominous silhouette, its sheer size dwarfing everything in its vicinity." << endl;
    cout << endl << "The gates, adorned with intricate carvings and imposing iron, creaked open reluctantly, as if burdened by the weight of centuries. Beyond them lay a sprawling courtyard, echoing with the footsteps of the countless souls who had traversed its expanse in eras long past. The enormity of the fort became apparent with every step, the scale of the edifice leaving visitors awestruck and humbled." << endl << endl;
    cout << "Ramparts, resembling the rugged spine of some ancient behemoth, lined the edges of the fort, offering panoramic views of the surrounding landscape. From this vantage point, one could see the vastness of the terrain that the fortress had stood guard over, a stoic witness to the eons that had swept across the region." << endl << endl;

    cout<<"The "<< palref <<" welcomes you at the gates of this massive beast and leads you to the artifact."<<endl<<endl<<"\"This here is what allows us to crush any armmy we've seen so far. We used it on a neighbouring raiding party; They disappeared without a trace. Nothing left behind. Not even their traces upon the sand.\""<<endl<<endl;
    cout<<"You grab the artifact." << endl << endl;
    inventory_amount[4]=inventory_amount[4]+1;
    cout<<"You hear two blood-curdling screams."<<endl<<endl<<"\"Guards, man the door!\""<<endl<<endl<<"He looks to you"<<"\"You better have had nothing to do with this.\""<<endl<<endl;
    cout<<"It's too little to late. The door bursts open, each guard is quickly taken down. An army of 20 well armed men take over, led by the insurgent leader."<<endl<<endl;
    if (cult==true){
        cout<<"You recognise him to be the man you found in the tunnels."<<endl<<endl;
        cout<<"\"There you are. My friend, you have granted us a great victory! Now hand me artifact and we may rule with the will of God\""<<endl<<endl;
        do{
            cout<<"The "<<palref<<" grabs you, and puts a knife to your throat."<<endl<<endl<<palref<<": \"I should have been weary of you from the start\". He looks at the leader."<<endl<<endl<<"\"Look, we can work this out, don't be rash. Let me go with the artifact, and we'll forget all about this \""<<endl<<endl;
            cout<<"(1) Charisma: Talk him down"<<endl<<"(2) Intelligence: Use your own knife and stab him"<<endl<<"(3) Strength: Flip him using his arms";
            cin>>choice;
            if ((choice==2)&&(inventory_amount[1]<1)){
                cout<<endl <<"You do not have a knife."<<endl;
            }
        } while ((choice>3)||(choice<1)||((choice==2)&&(inventory_amount[1]<1)));
        switch (choice)
        {
        case 1:
            if (cha_check(12)==true){
                cout<<endl<<"You talk him out of wanting to kill you, telling him he has no choice but to surrender. As he backs away from you, he is pierced by an arrow to the chest."<<endl<<endl;   
                cult_choice();
            }
            else{
                cout<<endl<<"He does not care for your musings. Understanding his situation, he jams his knife into your neck."<<endl<<endl;
                cout<<endl<<"You are try to scream but are unable to do so"<<endl<<endl;
            }
            break;
        
        case 2:
            if (intel_check(12)==true){
                cout<<endl <<"You stab him in the stomach twice and then some. He is a non factor"<<endl<<endl;
                cult_choice();
            }
            else{
                cout<<endl<<"He is able to percieve your uneasiness, and puts you out of your misery."<<endl<<endl;
                cout<<endl<<"You are dead"<<endl<<endl;
            }
            break;
        
        case 3:
            if (str_check(20)==true){
                cout<<endl <<"He lands on his lower back awkwardly, you keep his wrist in control and snap it. You hand him over to the group to as a prisoner of war."<<endl<<endl;                                                                                                       
                cult_choice();
            }
            else{
                cout<<endl<<"He is able to percieve your uneasiness, and puts you out of your misery."<<endl<<endl;
                cout<<endl<<"You are dead"<<endl<<endl;
            }
            break;
        }
    }
    else{
        cout<<"You enter into a standoff position against the assailants"<<endl<<endl;
        cout<<"\"Insurgent: Give us the artifact and save yourself a world of hurt.\""<<endl<<endl;
        do
        {
            cout<<"(1) Charisma: Talk your way past the conflict "<<endl<<"(2) Strength: Fight the entirety of the army "<<endl<<endl;
            cin>>choice;

        } while ((choice>2)||(choice<1));
        switch (choice)
        {
        case 1:
            if(cha_check(20)==true){
                cout<<"\"Fine, you plead your case well, you can go.\""<<endl<<endl;
                cout<<"You get out with your life but without the artifact, leaving a man to die."<<endl<<endl; 
                endings(1);
            }
            else{
                cout<<"They refuse to hear your pleas, you are now a captive of the anemey, scheduled for an execution"<<endl<<endl;
            }
            break;

        case 2:
             if(str_check(25)==true){
                cout<<"You single-handedly destroy the army."<<endl<<endl<<"The "<<palref<<" is awestruck"<<endl<<endl;
                endings(2);
             }
             else{
                cout<<"The army tears you piece to piece. What did you think was going to happen? You are dead."<<endl<<endl;
             }
            break;
        }
    }
}

void Mosque()
{

    UserMenu(5);
    cout << endl <<"The building is completely covered in white marble, the white walls decorated with calligraphic inscriptions. Encased within these beautiful walls, you enter a courtyard a fountain in the middle where believers come and perform ablution. There are tall towers radiating a call to prayer as you walk across the cold paved floor and marvel at the pearly white dome of the mosque." << endl;
    if (MosqueManInteraction==false)
     {
       MosqueMan();
     }
    else if (DjinnInteraction==false)
     {
       Djinn();
     }
    else 
    {
      cout << endl << "You do not know how to pray. It feels awkward, so you leave." << endl;
      UserMenu(0);
    }


}

void Coffee()
{
  string userin;
  int userint;
  UserMenu(6);
  cout << endl << "You see a building with ornate arches, intricate geometric patterns, and an outdoor seating area adorned with colorful tiles. The warm, earthy tones of the building lovingly invite you in." << endl;
  cout << endl << "The scent of coffee, freshly ground beans, and sugar wafts through the air as you open the wooden door to enter. Inside, you are welcomed by rich tapestries, textured fabrics, and mosaic tiles. The lamps hanging from the ceiling cast a warm and soft glow." << endl;
  if (ownerkilled == true)
   {
    cout << endl << "You see a young man who looks similar to the owner behind the counter. His eyes widen when he sees you. He yells, loudly: " << endl;
    cout << endl << "\"I saw you kill my father. Please leave, do not hurt any more of my family. \"" << endl;
    if(extortflag == false)
    {
    cout << endl << "He gives you 500 dinar as protection money and you leave. " << endl;
    extortflag = true;
    wallet+=500;
    UserMenu(0);
    }
    else 
     {
      cout << endl << "He has already paid for his protection. You leave. " << endl;
      UserMenu(0);
     }
   }
  if(CoffeeOwnerInteraction == false && cult == true)
    {
     cout << endl << "You find the owner behind a dark wooden counter, serving his customers. He is also making himself a cup of coffee on the side. " << endl;
     do{
     if(inventory_amount[1]>0)
       {
        cout << endl << "(1) Stab him with your dagger" << endl;
        cout << "(Note: This will remove the item from your inventory)" << endl;
       }
      if (inventory_amount[2]>0)
       {
        cout << "(2) Poison his coffee " << endl;
        cout << "(Note: This will remove the item from your inventory)" << endl;

       }
      if (strength>1)
      {
        cout << "(3) Beat him to death" << endl;
      }
     cout << "(4) Betray the cult " << endl;
     cout << "(5) Leave" << endl;
     cin>>userint;
     } while(userint<1 && userint>5);

     switch(userint)
      {
        case 1: cout << endl << "Wasting no time, you jump over the counter to slit his throat and stab him in the stomach. Blood sprays in all directions as he moves his body around trying to understand what is happening to him. The wooden counter turns red. Realizing the situation, he tries to call for someone, but his voicebox can produce only growls. It is a slow, painful death. You run back out to the streets." << endl;
                ownerkilled=true;
                inventory_amount[1] -=1;
                      CoffeeOwnerInteraction = true;
                UserMenu(0);
        break;
        case 2: cout << endl << "While he is distracted, you quickly sprinkle some poison into his coffee, making sure no one is watching. You get up and stand by the door. A few minutes later, you hear the owner scream in agony and collapse on the floor. A young man eyes you suspiciously, then rushes to the aid of the owner. You immediately leave the coffeehouse. " << endl;
               ownerkilled=true;
               inventory_amount[2] -= 1;
                     CoffeeOwnerInteraction = true;
               UserMenu(0);
        break;
        case 3: if(str_check(15)==true)
                  {
                    do{
                    cout << endl << "You take a deep breath and walk up to the counter. Without warning, you grab him by the collar and pull him towards you, dragging him across the wood. You throw him down on the ground. He begs you for mercy and offers you food worth 20 rations if you leave him alone, do you accept? " << endl;
                    cin >> userin;
                    } while (userin != "yes" && userin != "no");
                     if(userin == "no")
                      {
                        cout << endl << "\"You monster. You sick being. What do you want from me?\"" << endl;
                        cout << endl << "This angers you. You place your knees on his stomach and violently choke him to death." << endl;
                        cout << endl << "You leave the building panting. " << endl;
                              CoffeeOwnerInteraction = true;
                               ownerkilled=true;
                        UserMenu(0);
                      }
                     else
                     {
                      inventory_amount[3] += 20;
                      cout << endl << "You accept it and leave him alone. You give up your allegiance to the cult. " << endl;
                      cult = false;
                     }
                  }
                  else 
                  {
                    cout << endl << "You take a deep breath and walk up to the counter. Without warning, you grab him by the collar and try to pull him towards yourself. He does not move an inch. Furious, he vaults over the counter and smashes your head with a coffee cup. You clutch your head with both hands and start bleeding profusely. He kicks you out of the building." << endl;
                    cout << endl << "\"Come back when you need some coffee habibi,\" he taunts, \"or another ass beating!\"" << endl;
                   CoffeeOwnerInteraction = true;
                   strength = strength-2;
                    UserMenu(0);
                  }
        break;
        case 4: cout << endl << "You tell him of the cult's plan. He thanks you for not following through and gives you 10 rations and 300 dinar as a reward. " << endl;
               cout << endl << "\"That is how much our coffee costs, do feel free to try it!\"" << endl;
                    inventory_amount[3] += 20;
                    wallet+=300;
               cout << endl << "Knowing there was a hit on his head makes him anxious, and he closes shop while he recovers. " << endl;
                     CoffeeOwnerInteraction = true;
               UserMenu(0);
        break;
        case 5: 
              if (strength <= 1 && inventory_amount[1] <= 0 && inventory_amount[2]<=0)
              {
                cout << endl << "\"How was I planning on killing him, exactly?\"" << endl;
                UserMenu(0);
              }
             else
             {
              UserMenu(0);
             }
        break;

        default: Coffee();
      }

      CoffeeOwnerInteraction = true;
    }
  cout << endl << "\"Would you like some coffee?\" (300 dinar)" << endl;
  cin >> userin;
  if (userin == "yes" && strength <4)
   {
    cout << endl << "You enjoy a cup of coffee alone, taking in the conversation around you. This replenishes you, you leave the establishment feeling stronger. " << endl;
    wallet-=300;
    strength++;
    UserMenu(0);
   }
  else if (userin == "yes" && strength >=4) 
   {
    cout << endl << "Are you sure? Your strength is not low enough to be boosted by a cup of coffee."  << endl;
    cin >> userin;
     if (userin=="yes" || userin=="Yes") 
      {
       cout << endl << "You enjoy a cup of coffee alone, taking in the conversation around you. It tastes nice, but doesn't really do anything. You leave the establishment feeling like you just wasted 300 dinar. " << endl;
       wallet-=300;
       UserMenu(0);
      }
     else
      {
       cout << endl << "You change your mind and leave the coffeehouse. " << endl;
       UserMenu(0);
      }
   }
  else if (userin == "no" && strength <4)
   {
    cout << endl << "\"You look weak, habibi. Do consider drinking some, it'll make you feel better!\"" << endl;
    cin >> userin;
     if (userin=="yes" || userin=="Yes")
      {
       cout << endl << "You enjoy a cup of coffee alone, taking in the conversation around you. This replenishes you, you leave the establishment feeling stronger. " << endl;
       wallet-=300;
       strength++;
       UserMenu(0);
      }
     else 
      {
       cout << endl << "\"Your choice, my friend!\"" << endl;
       UserMenu(0);
      }
   }
  else if (userin == "no" && strength >=4)
   {
    cout << endl << "You forgot why you even came to the coffeehouse and leave. " << endl;
    UserMenu(0);
   }
  else  {Coffee();}
}

void Prison(int r)                                                                      //risk taken as parameter, influences bail
{
    int bail= r*10;
    string userin;
  cout<<endl<< "You are brought to prison. Your bail is " << bail <<  " dinar." << endl;
  bool boolstrength = str_check(15);
  if(wallet<bail && boolstrength==false)
  {
    cout << endl << "You do not have enough money to pay. You are ruthlessly beaten with sticks. The guards loot you for every penny you have and throw you out on the street. " <<endl;
    strength= strength-3;
    wallet = 0;
    UserMenu(0);
  }
  else if(wallet<bail && boolstrength==true)
  {
    cout << endl <<"You do not have enough money to pay. The guards try to beat you but you fight back. You still lose some strength in the process." << endl;
    strength= strength--;
    UserMenu(0);
  }
  else if (wallet>=bail && boolstrength==false)
   {
    cout << endl <<"You have enough money to pay, do you do it? " << endl;
    cin>>userin;
    if(userin=="yes"||userin=="Yes")
     {
      cout<<endl<<"You pay your dues and are free to go. " << endl;
      wallet = wallet-200;
      UserMenu(0);
     }
    else if (userin=="no" || userin=="No")
    {
      cout << endl<<"The guards demand twice the amount of your bail, you do not have the strength to fight them." <<endl;
      if(wallet>2*bail)
       {
        cout << "They extort the amount and shove you before leaving. Fortunately, you are not hurt. " << endl;
        wallet = wallet - 2*bail;
       }
       else 
        {
          cout << endl<< "You tell them you do not have that much money. Frustrated, they ruthlessly beat you with sticks and leave you sobbing on the street. They also take all of your money." << endl;
          strength = strength -2;
          wallet = 0;
        }
      cout << endl << "\"Curse this place,\" you mutter" << endl;
      UserMenu(0);
    }

   }

   else if (wallet>=bail && boolstrength==true)
   {
    cout << endl << "You have enough money to pay, do you do it? " << endl;
    cin>>userin;

    if(userin=="yes"||userin=="Yes")
     {
      cout<<endl<<"You pay your dues and are let go. You are now free. "<<endl;
      wallet = wallet - bail;
     UserMenu(0);
     }
    else if (userin=="no" || userin=="No")
    {
      cout << endl<<"The guards try to intimidate you but you fight back. You still lose some strength in the process." << endl;
      strength--;
      UserMenu(0);
    }

   }

}

void YellowCottage();

void BeigeHouse();

void BlueHouse()                                     //Citadel: Qazi's house
{

string userin;
int userint;
 if (GeneralInteraction == true || QaziInteraction==true)
  {
   cout<<endl<< "You knock, but no one answers. " << endl;
 do{
   cout << endl << "(1) Yellow cottage" << endl << "(2) Beige House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        YellowCottage();
       }
      else if (userint==2)
       {
        BeigeHouse();
       }
       else 
       {
        UserMenu(0);
       }
  }
 else if (charism>0) 
   {
     cout << "You knock, an old man with a white flowing beard answers. " << endl;
     caliph = Qazi();
   

     if (caliph == true && cult ==false)
     {
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "Qazi";
      phase++;
      lvl_up();
      UserMenu(0);
     }
    else if (caliph == true && cult== true)
    {
      if(CultInteraction==false)
      userint = 2;
     do {
       if (CultInteraction==true){
      cout << endl << "(1) Continue acting as a double agent" << endl << "(2) Betray the cult" << endl;
      cin >> userint;
       }
        } while (userint != 1 && userint != 2);
      if (userint == 1)
      {
       caliph = false;
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "Qazi";
      cout << endl << "You have succesfully gained The " << palref << "'s trust and infiltrated the government, however, your allegiance still lies with the cult." << endl;
      phase=phase+2;
      lvl_up();
         UserMenu(0);
      }
     else if (userint == 2)
      {
        caliph = true;
        cult = false;
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "Qazi";
      phase++;
      lvl_up();
      }
    if (cult == false && caliph == true)
     { cout << endl << "Before leaving, you reveal the cult's plans. The Qazi is very pleased with you, and gives you 1000 dinar as a reward." << endl;
     wallet +=1000;
      UserMenu(0);
     }
    }
    
    else 
     {
      cout << endl << "You are escorted out of the Citadel. " << endl;
      UserMenu(0);
     }

    
   }



  else 
  {
    cout <<endl<< "You knock, an old man with a flowing white beard answers. He looks confused, and slams the door in your face. " << endl;
 do{
   cout << endl << "(1) Yellow cottage" << endl << "(2) Beige House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        YellowCottage();
       }
      else if (userint==2)
       {
        BeigeHouse();
       }
       else 
       {
        UserMenu(0);
       }
    }


}


void BeigeHouse()                                                         //Citadel: General's house
{
 string userin;
 int userint;
 if (GeneralInteraction == true || QaziInteraction==true)
  {
     cout <<endl<< "You knock, but no one answers. " << endl;
 do{
   cout << endl << "(1) Yellow cottage" << endl << "(2) Blue House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        YellowCottage();
       }
      else if (userint==2)
       {
        BlueHouse();
       }
       else 
       {
        UserMenu(0);
       }
  }
 else if (charism>0) 
   {
    cout << endl << "You knock, a middle-aged man in a keffiyeh answers. " << endl;
    caliph = General();

    if (dead == true)
     {
      cout <<endl << "You are hung at the gallows in full view of the public." << endl;
     }
    else if (caliph == true && cult ==false)
     {
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "General";
      phase++;
      lvl_up();
      UserMenu(0);
     }
    else if (caliph == true && cult== true)
    {
      if(CultInteraction==false)
      userint = 2;
     do {
      if (CultInteraction==true){
      cout << endl << "(1) Continue acting as a double agent" << endl << "(2) Betray the cult" << endl;
      cin >> userint;
      }
       } while (userint != 1 && userint != 2);
      if (userint == 1)
      {
       caliph = false;
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "General";
      cout << endl << "You have succesfully gained The " << palref << "'s trust and infiltrated the government, however, your allegiance still lies with the cult." << endl;

      phase= phase+2;
      lvl_up();
         UserMenu(0);
      }
     else if (userint == 2)
      {
        caliph = true;
        cult = false;
      cout << endl << "He has taken you under his wing, you can now travel to the Royal \"Palace\" and the \"Fort\"." << endl;
      cout << endl << "(Note: Travelling to the Fort will trigger the final stage of the game)" << endl;
      cout << endl << "\"Listen carefully: when you go to seek audience with the Sultan, it is important that you wait until he has tended to all his matters; He will call you, do not speak out of turn.\"" << endl;
      palref = "General";
      phase++;
      lvl_up();
      }
    if (cult == false && caliph == true)
     { cout << endl << "Before leaving, you reveal the cult's plans. The General is very pleased with you, and gives you 1000 dinar as a reward." << endl;
     wallet +=1000;
      UserMenu(0);
     }
    }
    
    else 
     {
      cout << endl << "You are escorted out of the Citadel. " << endl;
      UserMenu(0);
     }

    
   }

  else 
  {
    cout << endl<<endl<< "You knock, a man in a keffiyeh answers. He looks annoyed, and slams the door in your face. " << endl;
 do{
   cout << endl << "(1) Yellow cottage" << endl << "(2) Blue House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        YellowCottage();
       }
      else if (userint==2)
       {
        BlueHouse();
       }
       else 
       {
        UserMenu(0);
       }
    }



}

void YellowCottage()                                                   //Citadel: Random house
{
    string userin;
    int userint;
    cout<<endl<< "You approach the yellow cottage, the door is wide open." << endl;
    cout <<endl<< "Do you enter?" << endl;
    cin>>userin;
    if(userin=="yes" && yellowhouse == false)
     {
      cout << endl << "You find some clothes and a dagger. You hurriedly leave the Citadel to avoid suspicion." << endl;
      inventory_amount[0] +=1;
      inventory_amount[1]+=1;
      yellowhouse = true;
      UserMenu(0); 
     }
    else if (userin == "yes" && yellowhouse == true)
     {
      cout << endl << "You find nothing of use. " << endl;
 do{
   cout << endl << "(1) Beige House" << endl << "(2) Blue House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        BeigeHouse();
       }
      else if (userint==2)
       {
        BlueHouse();
       }
       else 
       {
        UserMenu(0);
       }
     }
    else if (userin == "no")
    {
   do{
   cout << endl << "(1) Beige House" << endl << "(2) Blue House" << endl << "(3) Leave Citadel" << endl;
    cin>>userint;
   }while (userint <1 && userint >3);
      if (userint==1)
       {
        BeigeHouse();
       }
      else if (userint==2)
       {
        BlueHouse();
       }
       else 
       {
        UserMenu(0);
       }
    }
   else {YellowCottage();}

}

void Citadelin()                                                               //Inside the gates of the citadel
{
    int userint; 
    cout << endl;
    cout <<"As you stroll along the paved street within the Citadel, your gaze is captivated by a row of charming houses, each presenting an attractive facade. The houses are thoughtfully constructed around inviting courtyards, adorned with the soothing melody of fountains, the vibrant hues of blooming flowers, and the tranquil allure of calm pools. The air is filled with a refreshing ambiance that invigorates your senses, offering a welcome break.";
    cout << endl << endl <<"Your attention is irresistibly drawn towards two houses that stand out prominently amidst the enchanting scene. These residences, considerably larger than their neighbors, emanate an air of distinction. The first of these grand homes is painted in a serene shade of blue, its exterior reflecting the calm elegance within. The second, equally imposing, is adorned in a sophisticated beige, hinting at a refined interior that beckons exploration." << endl << endl << "The allure of the quaint yellow cottage from your earlier gaze persists, promising a unique charm that sets it apart within this tapestry of luxury. As you approach these homes, the anticipation of discovering the secrets concealed within their walls heightens. The Citadel's interiors hold the promise of stories, lavish details, and an immersive experience that transcends the ordinary, inviting you to step into a world where every corner whispers tales of opulence and mystery. "<<endl<<endl;
    cout <<"Which house do you first visit?" << endl;
    cout << endl <<"(1) Yellow" << endl << "(2) Blue" << endl << "(3) Beige" << endl;
    cin>>userint;
    if(userint == 1)
     {
        YellowCottage();
     }
    else if (userint == 2)
     {
        BlueHouse();
     }
    else if (userint == 3)
    {
        BeigeHouse();
    }
   else 
    {
      Citadelin();
    }
}

void Citadelguardsinteraction(int userint)       
{  string userin;
bool boolstrength = str_check(20);
    if(userint==2)
   {
    CitadelGuardsDialogue();
   }
  if((userint == 3) && (boolstrength==true))
   {
           cout << endl << "The guards put up a valiant effort, but ultimately lose." << endl;
           if(inventory_amount[1]>0)
           { cout << endl << "You have a dagger in your inventory." << endl;
            cout << endl << "(1) Kill and loot one of them"<< endl << "(2) Proceed towards the Citadel" << endl;
            cout << "(Note: Killing will remove one dagger from your inventory)" << endl;
            cin >> userint;
            if (userint == 1)
             {
              cout << endl << "You pull out your dagger and eye one of the guards. As you walk towards him, the guard grovels at your feet, begging you not to do it. He offers you 200 dinar, claiming it is all he has. You can hear him sobbing and reciting a prayer. Do you take pity?" << endl;
              cin >> userin;
                if(userin == "no")
                 {
                   cout << endl << "You stab him three times and leave him a bloody mess. It takes 10 long minutes for him to finally give out. You find 200 dinar and some bread in his pocket. " << endl;
                   inventory_amount[1] -=1;
                   wallet +=200;
                   inventory_amount[3] +=2;
                   Citadelin();
                 }
                else 
                 {
                  cout << endl << "You have mercy and accept the 200 dinar." << endl;
                  wallet+=200; 
                  Citadelin();
                 }
                             Citadelin();
             }
            else
              { Citadelin();} 
          }
        else 
         {
          Citadelin();
         }
   }
  else if ((userint == 3) && (boolstrength)==false)
      {
         cout << endl << "You try to put up a fight, but are beaten to a pulp before being kicked out back to the streets. You lose a significant amount of strength." << endl;
        strength=strength-2;
        UserMenu(0);
      }
}


int CitadelGate()
{
    int strength;
    bool citinflag=false;
    bool citgateflag = true;
   string userin;
   int userint;
   cout<<endl<<endl<<"Approaching the Citadel, the majestic fortress commands attention with its towering walls adorned in a brilliant coat of shiny white paint.Bathed in the radiant glow of the sun, the bricks exude a polished elegance, intricately pieced together to form an imposing yet finely crafted barrier. You wonder if you can scale this daunting wall. The Citadel stands as a testament to craftsmanship and a portal to a hidden world. Its surface tells tales of ancient battles and eras bygone through detailed decorations, offering a tantalizing glimpse into the world of the moneyed. " << endl;
   cout<< endl << "Within this walled sanctuary, a small yellow cottage stands out, radiating a warm charm that contrasts the grandiosity of the Citadel. As you explore the surroundings, the paradisiacal scene unfolds: a mosaic of manicured gardens and extravagant houses belonging to the Damascan elite. Majestic palm trees sway gracefully, casting shadows over the vibrant surroundings, while fragrant blossoms perfume the air. Yet, a formidable obstacle stands in the form of armed guards, vigilant in their duty. The dichotomy between the serene beauty of the gardens and the guarded environment leaves you two choices: be diplomatic to unravel the secrets within, or fight for your right to navigate this storied landscape?" << endl;
   cout << endl << "(1) Climb the wall" << endl << "(2) Talk to the guards" << endl << "(3) Fight the guards" << endl;
   cin>>userint;

   if(userint ==1)
    {
       do { cout<<endl<<"It is broad daylight, the guards see you and pull you down. They laugh at your moronic attempt."<<endl;
           cout << endl << "(2) Talk " << endl << "(3) Fight " << endl;
        cin >>userint;
       } while (userint != 2 && userint != 3);
  
        Citadelguardsinteraction(userint);
        
    }
   else if(userint ==2 || userint == 3)
    {
        Citadelguardsinteraction(userint);
    }
   else 
   {
    CitadelGate();
   }



}

void Travel(int i)
{                                                                                              
    int x;
    string loc;   
    string userin;                                                                         
     
    if(inventory_amount[3] == 1)
     {
      cout << endl << "WARNING: You have 1 ration left. Consider going to the Market and buying more. " << endl;
     }

   cout <<endl<<endl<< "Where would you like to go? ";
    cin >> loc;

      if (inventory_amount[3] <=0 )
     { do{
      cout << endl << "You have no rations. Would you like to travel anyway? " << endl;
      cin >> userin;
       if(userin == "yes")
        {
          cout << endl << "You collapse on your way to the " << loc <<  ". You never wake up again." << endl;
                      do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
       else if (userin == "no")
        {
          UserMenu(i);
        } 
     } while (userin != "yes" && userin != "no"); 
     }

    if(loc == "mosque" || loc == "Mosque")
     {
        x = 1;
       inventory_amount[3] -= 1;
     }
    else if(loc == "coffeehouse" || loc == "CoffeeHouse" || loc == "Coffeehouse")
     {
        x = 2;
      inventory_amount[3] -= 1;

     }
     else if(loc == "palace" || loc == "Palace")
     {
        x = 3;
       inventory_amount[3] -= 1;
     }
   else if(loc == "citadel" || loc == "Citadel")
     {
        x = 4;
       inventory_amount[3] -= 1;
     }
    else if(loc == "market" || loc == "Market")
     {
        x = 5;
       inventory_amount[3] -= 1;
     }
   else if(loc == "fort" || loc == "Fort")
     {
        x = 6;
       inventory_amount[3] -= 1;
     }
     else
      {cout <<endl<<endl<< "You travel around Damascus for hours, but you cannot find a place called " << "\"" << loc << "\"" << " anywhere." << endl;
      cout << endl << "You waste 1 ration and lose some strength." << endl << endl;
      inventory_amount[3] -= 1;
      strength--;
      }
     
    switch (x)
    {case 1 : Mosque();
     break;
     case 2 : Coffee();
     break;
     case 3 : Palace();
     break;
     case 4 : CitadelGate();
     break;
     case 5 : Market();
     break;
     case 6 : Fort();

     break;

     default: Travel(i);
    }
}



void Stats(int i)
{
    cout << endl << "Strength: " << strength << endl << "Intelligence: " << intel << endl << "Charisma: " << charism;
    cout << endl;
    if (wallet>0)
    {
    cout << endl << "You have " << wallet << " dinar to your name. " << endl;
    }
    else
     {
      cout << endl << "You have no money. Consider selling something at the market. You can also use the steal function when at a location. (Beware: this could have consequences!) " << endl;
     }
    UserMenu(i);
}

int StreetInteraction1 ()                    //drunk
{
    string userin;
    int userinint;
     cout << endl << "You see a man stumbling his way through the crowd in ragged clothing. He seems to be talking to himself. Do you approach him?" << endl;
     cin>> userin;
    if((userin=="yes" || userin == "Yes") && intel<4)
     {
       streetinter1 = true;
       cout << endl << "\"Hey, you. I love you.\""  << endl;
       cout << endl<< "(1) \"What?\" " << endl << "(2) \"I love you too\" " << endl << "(3) \"You're drunk.\" " << endl;
       cin >> userinint;
       if(userinint == 1)
       {
         cout << endl << "\"I said I love you. Aren't you glad to be alive? I'm so happy I get to share this moment with you.\"" << endl ;
         cout << endl << "1: uhh, I guess?" << endl << "2: Yes! " << endl << "3: No, not really." << endl;
         cin>>userinint;
         if(userinint==1)
          {
             cout << endl << "\"You're no fun. I'll go talk to someone else.\" " << endl;
                     UserMenu(0);
          }
        else if (userinint==2)
         {
             cout << endl << "\"Shukran!\"" << endl;
                     UserMenu(0);
         }
        else if(userinint == 3)
        {
             cout << endl << "\"Makbul. You will die alone.\" " << endl;
                     UserMenu(0);
        }
        else
        {
            UserMenu(0);
        }
       }
      else if (userinint == 2)
       {
        cout << endl << "\"Shukran!\"" << endl;
                UserMenu(0);
       }
      else if (userinint == 3)
      {
       cout << endl << "\"No, YOU'RE drunk.\"" << endl;
               UserMenu(0);
      }
      else
      {
        UserMenu(0);
      }
     }
    else if((userin=="yes" || userin == "Yes") && intel_check(15)==true)
     {  streetinter1 = true;
        cout << endl << "You know that being drunk in public in the Caliphate is a crime. You can hand the man over to the authorities. Do you do it?" << endl;
        cin>>userin;
        if(userin == "yes" || userin == "Yes")
         {
            cout << endl << "You hand him over to the police. You are awarded 100 dinar for your troubles. " << endl;
            wallet += 100;
            UserMenu(0);
         }
        else 
        {
         cout << endl << "\"Hey, you. I love you.\""  << endl;
       cout << endl<< "(1) \"What?\" " << endl << "(2) \"I love you too\" " << endl << "(3) \"You're drunk.\" " << endl;
         cin >> userinint;
         if(userinint == 1)
         {
           cout << endl << "\"I said I love you. Aren't you glad to be alive? I'm so happy I get to share this moment with you.\"" << endl ;
           cout << endl << "1: uhh, I guess?" << endl << "2: Yes! " << endl << "3: No, not really." << endl;
           cin>>userinint;
           if(userinint==1)
           {
            cout << endl << "\"You're no fun. I'll go talk to someone else.\" " << endl;
               UserMenu(0);
           }
          else if (userinint==2)
           {
             cout << endl << "\"Shukran!\"" << endl;
                UserMenu(0);
           }
          else if(userinint == 3)
          {
               cout << endl << "\"Makbul. You will die alone.\" " << endl;
                  UserMenu(0);
          }
          else
          {
              UserMenu(0);
          }
         }
      else if (userinint == 2)
       {
        cout << endl << "\"Shukran!\"" << endl;
           UserMenu(0);
       }
      else if (userinint == 3)
      {
       cout << endl << "\"No, YOU'RE drunk.\"" << endl;
          UserMenu(0);
      }
      else
      {
        UserMenu(0);
      }
    }
              
     }
    else
    {
       cout << endl << "You see him say \"I love you\" to everyone he stumbles into, before disappearing into the crowd." << endl;
       streetinter1 = false;
       UserMenu(0);
    }
}

int StreetInteraction2 ()                    //conman
{  
  string userin;
  cout << endl << "You see a salesman on the street. Do you approach him? " << endl;
  cin >> userin;

  if(userin == "yes" || userin == "Yes")
  {
    streetinter2 = true;
    cout << endl<<"He offers you a potion to make you stronger, smarter and more charismatic. It costs 400 dinar. Do you buy it?" << endl;
    cin>>userin;
    if(userin == "yes" || userin == "Yes")
     {
        if (wallet>400)
        {
        cout << endl << "He hands you the potion. As soon as you hand him the money, he sprints in the opposite direction, disappearing into the crowd." << endl;
        cout <<endl<< "You drink the potion. It does nothing. You feel stupid and stare at the pavement for a while. "<<endl ;
        wallet-=400;
        UserMenu(0);
        }
       else
       {
        cout << endl << "You do not have enough money for the potion." << endl;
        cout << endl << "\"I can see you are struggling. You know what? Just for you my friend, you can have it for " << wallet << " dinar. \" " << endl;
        cout << endl << "You wonder how he knows the exact amount of money on you. Do you ask him? " << endl;
        cin >> userin;
        if(userin == "yes" || userin == "Yes")
         {
            cout << endl << "Tricks of the trade, my friend. I've used the potion myself. Do you want it or no?" << endl;
            cin>>userin;
            if(userin=="yes" || userin=="Yes")
             {
                cout << endl << "He hands you the potion. As soon as you hand him the money, he sprints in the opposite direction, disappearing into the crowd." << endl;
                cout <<endl<< "You drink the potion. It does nothing. You feel stupid and stare at the pavement for a while. You are destitute. "<<endl ;
                wallet = 0;
                UserMenu(0);
             }
            else 
            {
              cout << endl << "\"Well, your loss.\"" << endl;
              UserMenu(0);            
            }
        }
         else
         {
            cout << endl << "\"So? What do you say? Do you want it?\" " << endl;
            cin>>userin;
            if(userin=="yes" || userin=="Yes")
             {
                cout << endl << "He hands you the potion. As soon as you hand him the money, he sprints in the opposite direction, disappearing into the crowd." << endl;
                cout <<endl<< "You drink the potion. It does nothing. You feel stupid and stare at the pavement for a while. You are destitute. "<<endl ;
                wallet = 0;
                UserMenu(0);
             }
            else 
            {
              cout << endl << "\"Well, your loss.\"" << endl;
              UserMenu(0);            
            }
         }
       }
     }
    else 
     {
        cout << endl << "You try to leave, but he shouts at you to come back. He offers you 250 dinas for the potion. Do you buy it?" << endl;
        cin>>userin;
        if(userin== "yes" || userin == "Yes")
         {
           cout << endl << "He hands you the potion. As soon as you hand him the money, he sprints in the opposite direction, disappearing into the crowd" << endl;
           cout <<endl<< "You drink the potion. It does nothing. You feel stupid and stare at the pavement for a while. "<<endl ;
           wallet -=250;
           UserMenu(0);
         }
        else
         {
            cout << endl << "\"Well, your loss.\"" << endl;
           UserMenu(0);
         }
     }
  }
  else 
   {
    streetinter2 = false;
    UserMenu(0);
   }

}

bool ChanceEncounter()                                 //randomizes order of chance encounters 
{
srand(time(0));
 int x = rand() % 100 + 1;
 if(x%2 == 0) 
  {
    return true;
  }
 else 
  {
    return false;
  }
}


int UserMenu(int i)
{
    int num;
    bool chanceencounter=ChanceEncounter(); 
    if (dead == true)
     {
                  do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
     } 
    if(cult==0 && MosqueManInteraction==true && phase == 1 ) 
    {
      cout << endl << "You are lost without purpose. You roam around the city and cannot make sense of anything. No one around you believes your situation and you are outcast. You live as a vagrant for the rest of you life and die in a foreign place in a different time, never knowing what happened to you or why." << endl;
                  do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
    }
    if(ownerkilled==true && CultInteraction == false)
     {
      cult_2();
     }             
    cout <<        "______________________________";                                      
    cout <<endl << "You are at The " << loc[i] << ". " << endl;                  // i is the index of location array
    cout<<endl<<"Enter \"1\" to check your inventory, Enter \"2\" to travel, Enter \"3\" to steal from your location," << endl;
    cout<<"Enter \"4\" to check your stats, " << "Enter \"5\" to continue (exit menu), " << "Enter \"6\" to view objectives."<<endl;
    cout << "_______________________________________________________________________________________________";
    cout << endl;
    cin>> num;
    string loc;

    if(num==5 && i==0)
    {
    if(chanceencounter == true && streetinter1 == false)
       {
          StreetInteraction1();
       }
    else if (chanceencounter == false && streetinter2 == false)
      {
         StreetInteraction2();
      }
    else if (streetinter1 == true && streetinter2 == true)
    {     
      cout << endl<< "You have no business on the streets. You must travel somewhere. (Game: You have experienced all the random encounters in this location) " << endl;
      UserMenu(0);
    }
    else 
     {cout << endl<< "You have no business on the streets. You must travel somewhere. " << endl;
      UserMenu(0);
    }
    }

    switch(num)
    {
        case 1: display_inventory(i);
        break;
        case 2: Travel(i);
        break;
        case 3: if (i==0) {Search(i,medrisk);}
                else if (i==1) {Search(i,highrisk);}
                else if (i==2) {Search(i,insanerisk);}
                else if (i==3) {Search(i,insanerisk);}                                        //palace and fort ridiculous places to try and rob
                else if (i==4) {Search(i,lowrisk);}
                else if (i==5) {Search(i,medrisk);}
                else if (i==6) {Search(i,medrisk);}
        break;
        case 4: Stats(i);
        break; 
        case 5: return 0;
        break;
        case 6: objectives(i);
        break;

       default: UserMenu(i);
    }
}



void Intro()
{
    string ures;
    int urint;
    char x;
    int count = 0;
    cout << endl << endl << "You wake up in your slipknot T-shirt. Your hand reaches for your lamp, but it is not where it usually is. In fact, in the dark, nothing is where it's supposed to be. Confused, you look around; Spiral stairs near the door climb the circular walls, the smell of woodwork and candle wax wafts through the air. You realize this is not your bedroom. There is a lock on the door, no keys to be found. The small room is dimly lit but you can still make out a hole in the ground next to the door which seems to lead to a tunnel of some kind. " << endl << "You are thirsty, but don't really feel like getting up." << endl;
     cout << endl << "(1)Climb the stairs" << endl << "(2)Enter the tunnel " << endl << "(3)Go back to sleep "  << endl;
    cin >> urint;
    if (urint == 1) 
     {
      cout << endl << "You climb the to top of the tower using the stairs. It leads to a roof." << endl<< endl << "The sky is a radiant orange. You can see the bustling markets, beggars harrassing people, droves of people walking to and from places using paved streets." <<endl<< endl << "Mosques, forts, a palace in the distance. From your internet rabbitholes, you can tell this is medieval Damascus. You are confused; Not knowing what else to do, you go back down." << endl<<endl<< "You do not know where you are, but you are definitely not home. You go back to sleep hoping to wake up from the dream."<<endl;
     }
    else if (urint == 3)
    {
        do
         {
          cout << endl << "You wake up again, even more dehydrated than before. Do you go back to sleep?" << endl;
          cin >>ures;
          count++;
          if (count > 6) 
           {
            cout << endl << "You die of dehydration in your sleep." << endl;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
           }
         } while(ures == "yes");

      if (count > 2)
       {
        cout << endl << "You try to get up but can't; Your body is too dehydrated to do anything. You die writhing in agony, cursing your laziness." << endl;
                    do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
       }

         cout << endl << "You climb the top of the tower using the stairs. It leads to a roof." << endl << "The sky is orange, you can see the bustling markets, beggars harrassing people, droves of people walking to and from places." << endl << "Mosques, forts, a citadel in the distance. From your internet rabbitholes you can tell this is medieval Damascus." << endl << "You are confused, not knowing what else to do, you go back down." << endl<< "You do not know where you are, but you are definitely not home. You go back to sleep, hoping to wake up from the dream." << endl;

       
    }
  else if (urint == 2)
   {
      cult_lead();
       cout << endl << "Out of curiosity, you climb the top of the tower using the stairs. It leads to a roof." << endl << "The sky is orange, you can see the bustling markets, beggars harrassing people, droves of people walking to and from places." << endl << "Mosques, forts, a citadel in the distance. From your internet rabbitholes you can tell this is medieval Damascus." << endl << "You are confused, not knowing what else to do, you go back down." << endl<< "You do not know where you are, but you are definitely not home. You go back to sleep, hoping to wake up from the dream." << endl;

   }
   else 
    {
      Intro();
    }
    
    cout << endl << endl << "Press x to continue" << endl;
    cin >> x;
  if(x == 'x')
  {

    cout << endl << endl;
    cout << "You wake up again to find the lock has disappeared. There are some clothes lying on the floor." << endl << "Next to them, some coins, bread and a note written in Arabic. You have never spoken a word of Arabic, but are able to read it perfectly well:" << endl <<endl << "\"Wear to survive.\" " << endl ;
    cout << endl << "Do you wear them?" << endl;
    cin >> ures;
    
    if (ures == "no" || ures == "No")
     {
        cout << endl << "You go outside. Fascinated by your clothes, a crowd gathers around you, gasping and murmuring among themselves. You try to leave, but a large man from the crowd jumps out and holds you down." << endl;
        cout << endl << "Do you fight back?" << endl;
        cin >> ures;
       if (ures == "yes" || ures == "Yes")
        {
            cout << endl << "You try to fight back but another man emerges from the crowd, unsheathes his sword, and stabs you. You bleed to death on the cold hard floor." << endl;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        }
      else 
       {
        cout << endl << "You make peace with the situation. You are handed to the court. Someone tries to talk to you but is forced out. You could not understand what he was saying. You are asked to identify yourself. Do you tell the truth?" << endl;
        cin >>ures;
        if (ures == "yes" || ures == "Yes")
         {
            cout << endl << "You speak, trembling: " << endl;
            cout << endl << "\"Your Honour, I am not from this time. I am from the future. I have no idea how this happened, please, let me go so I can figure this out.\"" << endl;
            cout << endl << "The Qazi rules that you are insane and banishes you. You starve to death in the desert." << endl;
                        do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
         }
         else
         {
            cout << endl << "You decide to lie." << endl << "Do you tell the Qazi you are (1) a traveller, (2) a foreigner or (3) the antichrist?" << endl;
            cin >> urint;
             if (urint == 1 || urint == 2)
              {
                cout << endl << "The Qazi believes you and lets you go. Upon hearing of a very peculiar outlander wearing interesting clothes, a target is set on your head and you are mugged by masked bandits as soon as you leave the court. They kill you to avoid retribution.";
                            do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;

              }
            if (urint == 3)
            {
                cout << endl << "You say, grinning: " << endl;
                cout << endl << "\"I am Dajjal, the day of judgement is upon us. Let me go and I might spare your life. Otherwise, feel free to bear the consequences.\"" << endl;
                cout << endl <<"In a shocking turn of events, the Qazi does not believe you. You are still sentenced to death just for good measure. Your last memory is of a swarm of stones being hurled at you." ;
                            do {
    cout <<endl<< "Press x to exit" << endl;
    cin>>usrexit;
    } while (usrexit != 'x');
        exit(0);;
        

            }
         }
       }
     }
     else
     {
       cout << endl << endl << "You go outside. You get a few looks but everyone goes about their business as usual. " << endl ;
     }
  }
}


int main()
 {
       set_attr();
       Intro();
      cout << endl << "You see a \"mosque\" on the horizon and a \"coffeehouse\" nearby, as well as a \"market\" out in the open."<< endl <<endl<< "(INSTRUCTIONS: Use the travel function and type the names of these locations correctly to visit them. Not typing them correctly will have negative consequences. You consume 1 ration everytime the travel function is used; Use the inventory to keep track of your rations. You can always buy rations from the Market. Once you are at your desired location, exit the menu (5) to access the location/move the game forward). You can also press 5 when you are on the streets. If you are lost, the objectives function (6) may contain a hint. " << endl;
      UserMenu(0);
}