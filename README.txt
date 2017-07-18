Nume: Piersicanu Radu Stefan
Grupa: 332CB

Utilizare aplicatie:
	-taste miscare: W-sus, A-stanga, S-jos, D-dreapta
	-mouse: nava tinteste in directia mouse-ului si trage la click stanga

Implementare:
	-Clase:
		-GameObject - clasa de baza din care sunt extinse toate obiectele din joc:
						Player,Enemy1,Enemy2,Enemy3,Boss,Projectile,Boss_Proj
					- contine vectori ce retin instante ale obiectelor:
						enemyQueue(inamici ce urmeaza sa fie adaugati invectorul de inamici)
						projectiles(proiectilele player-ului)
						enemies
						boss_projs(proiectilele generate de boss)
					- contine 2 functii statice:
						GenEnemyPos() -> genereaza pozitia initiala a inamicilor
										in functie de distanta dintre player si marginea jocului
						Collision(o1, o2, radius) -> verifica distanta dintre 2 obiecte si o
													compara cu raza de coliziune
		-clasele ce extind clasa GameObject contin cate un constructor ce genereaza datele initiale
		ale instantelor obiect si GameObject_update() ce updateaza pozitia obiectelor in scena
		
		-Enemy1 inamic simplu cu o viata
		-Enemy2 2 vieti, atunci cand ramane cu o viata se micsoreaza dimensiune si se dubleaza viteza
		-Enemy3 atunci cand e distrus genereaza 2 Enemy1 la distana unul fata de celalalta
		-Boss inamic cu 50 de vieti generat atunci cand au fost distrusi 50 de inamici
				apare in partea de sus a ecranului si se misca pe axa OX in functie de sin(elapsedTime)
Functionalitati:
	-inamicii sunt generati in jurul player-ului in functie de cea mai mica distanta dintre player si margine
	cu o raza minima de 15
	-coliziunea este verificata in GeoWars::Update
	-obiectele sunt desenate pe ecran in GeoWars::DrawScene