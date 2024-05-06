## **Project Saved**

**Meet the Team:** 
Jacob Marsh - Project Manager
Gunner La Mar - DJ Bridges
Brandon Beene - Screenwriter
Juvraj Shergill - Taster Tester
Joshua Garza - Special Grade Curse User
Isael Cardenas - Lord of the Threads
Angel Orozco - Socketroth

## **LORE DUMP**
" *...*You are free. Now free us from our everlasting dreams. You are like us*...* "

With these words echoing in his head, our [Hero](https://creator.nightcafe.studio/creation/3xcnHOWpZMxBnKIqPW87?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) finds themself marooned on a derelict ship in space. Missing crucial memories, the Hero must navigate through the ship battling monsters and the unknown in order to piece together their fractured mind, ultimately culminating in a final decision that will shape the fate of Humanity moving forward, thus winning the game.

[The GNP](https://creator.nightcafe.studio/creation/BloH2vzrrio87ZWnFUqU?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) aka (The Global Nations Protection Unit) - A worldwide effort by the people of Earth, that was formed during the First Kemon Invasion, in order to defend against the warmongering alien race.

[The Arcius](https://creator.nightcafe.studio/creation/pnGqx0IcKozxJ6lDvFUI?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) - An Ark-class Dreadnaught shuttle built by the brightest of humanity in order to take to the stars once the war decimated Earth.

[K.O.R.I](https://creator.nightcafe.studio/creation/IH5XS7bzcqTHfrEA0O2k?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) aka (Kemon Observational Reconnaissance Intelligence) -  An A.I with the purpose of storing information about the Kemon race, and reporting it back to the GNP.

[Kemons](https://creator.nightcafe.studio/creation/flVibnK0wYOL6Nhvqjt7?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) - An alien race that attempted to take over the Earth, but have slowly ended up razing it in the process. Has other [variants](https://creator.nightcafe.studio/creation/GOq6oMpzWnZpsNwEGh0H?ru=6fJ89bwOwrNPv6bar7eOcbfUkOb2) depending on what obstacles lie in their path.

## **Development Process**

The first thing we tried to do, was hammer out the story that we all wanted to tell. We had immediately decided on a Sci-fi theme, with a main focus on piecing together the memories of our Hero in order to discover just what happened on board this ship and how they got there.

In keeping with wanting to have a solid story planned from the beginning as a foundation, I also wanted to prioritize finishing the music for the game that way we could have the vibe and tone of the game set in stone. So in order to accomplish this, Gunner went to work as our resident DJ Bridges, and set about creating the music for the game using a website called BeepBox.co. He created two songs for the project, one for the main overworld, and one for when the player is in combat.

The Taste Tester Juvraj, ran into the bulk of their issues with setting up tests for the code using GTest, where it was failing to compile, as well as our Curselord Joshua running into issues working with Dear Imgui since it was a new bit of software for our Curselord to work with. This led to frustration with images refusing to generate, or displaying incorrectly as a blank screen. These issues were sorted out in time with the compilier issue being sorted, and in the case of Dear Imgui, we were able to generate the images we wanted for the game UI.

Our Socketroth role was chosen by Angel, who worked on making sure that networking was properly implemented  so that the game could function in multiplayer coop.

There were two roles in this project that were unable to be fulfilled since we did not have a full team: 
The Inheritor of Suffering, who would be responsible for creating a class hierarchy for the game.
The Integration Specialization Amalgamation Decimation or (ISAD), who would be responsible for linking all the parts worked on throughout the group in order to make a functioning game out of it.

## ** Workflow **
```mermaid
     graph LR;
        Start-->Story ;
	     Start-->Music;
	     Story-->UI;
	     Music-->UI;
	     UI-->Networking;
	     Networking-->Multithreading;
	     Multithreading-->Testing;
	     Testing-->Readme;
	     Testing-->Essay;
	     Readme-->END;
	     Essay-->END;
       

