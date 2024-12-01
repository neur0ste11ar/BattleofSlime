#include "engine.h"

shared_ptr<Slime> loadPlayer(shared_ptr<Player> player)
{
	map<string, shared_ptr<Skill>> skills = parseSkills("skills.xml");
	map<string, shared_ptr<Slime>> slimes = parseSlimes("slimes.xml", skills);
	/*stringstream ss;
	ss << "You can select 3 from " << slimes.size() << " (";
	int i = 0;
	for (const auto& pair : slimes) {
		ss << ++i << " for " << pair.first;
		if (i < slimes.size()) {
			ss << ", ";
		}
	}
	ss << ").";
	cout << ss.str() << endl;

	vector<shared_ptr<Slime>> selectedSlimes;
	string firstSlime;
	while (selectedSlimes.size() < 3)
	{
		cout << "Select your " << selectedSlimes.size() + 1 << " slime: ";
		int index;
		cin >> index;
		if (cin.fail() || index < 1 || index > slimes.size())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		auto iter = next(slimes.begin(), index - 1);
		if (find(selectedSlimes.begin(), selectedSlimes.end(), iter->second) == selectedSlimes.end())
		{
			iter->second->setPlayer(1);
			selectedSlimes.emplace_back(iter->second);
		}
	}*/
	vector<shared_ptr<Slime>> selectedSlimes;
	cout << "You can select three from five (1 for Green, 2 for Red, 3 for Blue, 4 for Yellow, 5 for Pink)." << endl;
	while (selectedSlimes.size() < 3)
	{
		if (selectedSlimes.size() == 0) {
			cout << "Select your 1st slime: ";
		}
		else if (selectedSlimes.size() == 1) {
			cout << "Select your 2nd slime: ";
		}
		else {
			cout << "Select your 3rd slime: ";
		}
		int index;
		cin >> index;
		if (cin.fail() || index < 1 || index > slimes.size())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			continue;
		}
		shared_ptr<Slime> slime;
		switch (index) {
			case 1:
				slime = slimes["Green"];
				break;
			case 2:
				slime = slimes["Red"];
				break;
			case 3:
				slime = slimes["Blue"];
				break;
			case 4:
				slime = slimes["Yellow"];
				break;
			case 5:
				slime = slimes["Pink"];
				break;
		}
		if (find(selectedSlimes.begin(), selectedSlimes.end(), slime) == selectedSlimes.end())
		{
			slime->setPlayer(1);
			selectedSlimes.emplace_back(slime);
		}
	}
	
	player->setSlimes(selectedSlimes);
	cout << "You have " << selectedSlimes[0]->getName() << ", " << selectedSlimes[1]->getName() << " and " << selectedSlimes[2]->getName() << ", starting with " << selectedSlimes[0]->getName() << endl;

	return selectedSlimes[0];
}

shared_ptr<Slime> loadEnemySun(shared_ptr<EnemySun> enemy)
{
	map<string, shared_ptr<Skill>> skills = parseSkills("skills.xml");
	map<string, shared_ptr<Slime>> slimes = parseSlimes("slimes.xml", skills);

	vector<shared_ptr<Slime>> selectedSlimes;
	slimes["Pink"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Pink"]);
	slimes["Green"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Green"]);
	slimes["Red"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Red"]);

	enemy->setSlimes(selectedSlimes);

	cout <<"Enemy has Pink, Green and Red, starting with Pink." << endl;

	return selectedSlimes[0];
}

shared_ptr<Slime> loadEnemyRain(shared_ptr<EnemyRain> enemy)
{
	map<string, shared_ptr<Skill>> skills = parseSkills("skills.xml");
	map<string, shared_ptr<Slime>> slimes = parseSlimes("slimes.xml", skills);

	vector<shared_ptr<Slime>> selectedSlimes;
	slimes["Green"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Green"]);
	slimes["Blue"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Blue"]);
	slimes["Yellow"]->setPlayer(2);
	selectedSlimes.emplace_back(slimes["Yellow"]);

	enemy->setSlimes(selectedSlimes);

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine engine(seed);
	uniform_int_distribution<int> distribution(0, 2);
	int randomNumber = distribution(engine);

	cout << "Enemy has Blue, Green and Yellow, starting with " << selectedSlimes[randomNumber]->getName() << "." << endl;

	return selectedSlimes[randomNumber];
}

bool sortSequence(Effect& effect1, Effect& effect2)
{
	if (effect1.act->getPriority() > effect2.act->getPriority()) {
		return true;
	}
	else if (effect1.act->getPriority() < effect2.act->getPriority()) {
		return false;
	}
	else {
		if (effect1.self->getSpeed() > effect2.self->getSpeed()) {
			return true;
		}
		else if (effect1.self->getSpeed() < effect2.self->getSpeed()) {
			return false;
		}
		else {
			return effect1.self->getPlayer() == 2;
		}
	}
}

void execute(Effect& effect, shared_ptr<Field> field, bool& singFlag)
{
	Result result = effect.act->activate(effect.self, effect.target, field);
	if (effect.self->isAlive()) {
		cout << endl;
	}
	singFlag = false;
	singFlag = (effect.action == change) || (effect.action == potion) || (result == failure);
}

bool checkEnd(shared_ptr<Player> player1, shared_ptr<Player> player2, shared_ptr<Field> field)
{
	if (player1->aliveNum() == 0) {
		cout << "You lose" << endl;
		return true;
	}
	if (player2->aliveNum() == 0) {
		cout << "You win" << endl;
		return true;
	}
	if (field->getTurns() == 100) {
		cout << "Draw" << endl;
		return true;
	}
	return false;
}

Sprite* loadSlimePic(shared_ptr<Slime> slime)
{
	Sprite* slimePic = gcnew Sprite("SlimeGrass.png");
	switch (slime->getElement()) {
		case grass:
			slimePic = gcnew Sprite("SlimeGrass.png");
			break;
		case fire:
			slimePic = gcnew Sprite("SlimeFire.png");
			break;
		case water:
			slimePic = gcnew Sprite("SlimeWater.png");
			break;
		case electric:
			slimePic = gcnew Sprite("SlimeThunder.png");
			break;
		case normal:
			slimePic = gcnew Sprite("SlimeNormal.png");
			break;
	}
	return slimePic;
}

Sprite* loadSlimePic_r(shared_ptr<Slime> slime)
{
	Sprite* slimePic = gcnew Sprite("SlimeGrass_r.png");
	switch (slime->getElement()) {
	case grass:
		slimePic = gcnew Sprite("SlimeGrass_r.png");
		break;
	case fire:
		slimePic = gcnew Sprite("SlimeFire_r.png");
		break;
	case water:
		slimePic = gcnew Sprite("SlimeWater_r.png");
		break;
	case electric:
		slimePic = gcnew Sprite("SlimeThunder_r.png");
		break;
	case normal:
		slimePic = gcnew Sprite("SlimeNormal_r.png");
		break;
	}
	return slimePic;
}

void loadScene(shared_ptr<Field> field)
{
	Window::setSize(1375, 792);
	auto scene = gcnew Scene;
	SceneManager::enter(scene);
	shared_ptr<Slime> slime1 = field->getSlimes().first;
	shared_ptr<Slime> slime2 = field->getSlimes().second;
	auto backgroud = gcnew Sprite("background.png");
	scene->addChild(backgroud);
	auto slime1Pic = loadSlimePic(slime1);
	slime1Pic->setScale(0.3);
	slime1Pic->setPos(180, 500);
	scene->addChild(slime1Pic);
	auto slime2Pic = loadSlimePic_r(slime2);
	slime2Pic->setScale(0.3);
	slime2Pic->setPos(970, 500);
	scene->addChild(slime2Pic);
	auto healthPic1 = gcnew Sprite("menu.png");
	healthPic1->setOpacity(0.6);
	healthPic1->setPos(260, 700);
	scene->addChild(healthPic1);
	auto healthPic2 = gcnew Sprite("menu.png");;
	healthPic2->setOpacity(0.6);
	healthPic2->setPos(1050, 700);
	scene->addChild(healthPic2);
	auto health1 = gcnew Text(to_string(slime1->getHealth()) + "/" + to_string(slime1->getMaxHealth()));
	health1->setAnchor(0.5, 0.5);
	health1->setPos(325, 725);
	health1->setFontSize(25);
	health1->setStrokeColor(Color::Black);
	scene->addChild(health1);
	auto health2 = gcnew Text(to_string(slime2->getHealth()) + "/" + to_string(slime2->getMaxHealth()));
	health2->setAnchor(0.5, 0.5);
	health2->setPos(1115, 725);
	health2->setFontSize(25);
	health2->setStrokeColor(Color::Black);
	scene->addChild(health2);
	auto sleep = gcnew Sprite("IconSleep.png");
	auto paint = gcnew Sprite("IconPaint.png");
	int count = 0;
	if(slime1->isSleeping()) {
		count++;
		sleep->setPos(185, 600);
		scene->addChild(sleep);
	}
	if (slime1->isPainted()) {
		if (count == 0) {
			paint->setPos(185, 600);
		}
		else {
			paint->setPos(185, 635);
		}
		scene->addChild(paint);
	}
	count = 0;
	if (slime2->isSleeping()) {
		count++;
		sleep->setPos(1215, 600);
		scene->addChild(sleep);
	}
	if (slime2->isPainted()) {
		if (count == 0) {
			paint->setPos(1215, 600);
		}
		else {
			paint->setPos(1215, 635);
		}
		scene->addChild(paint);
	}
	easy2d::Timer::add([=]() {
		easy2d::Game::quit();
		}, 0.01f);
	Game::start();
}

void playGame(shared_ptr<Player> player1, shared_ptr<Player> player2, shared_ptr<Field> field)
{
	if (Game::init())
	{
		while (true) {
			field->updateField();
			loadScene(field);

			field->setTurns(field->getTurns() + 1);
			cout << "Round " << field->getTurns() << endl;

			Effect player1Effect = player1->selectAct(nullptr, field);
			Effect player2Effect = player2->selectAct(player2, field);

			if (player1Effect.action == escape) {
				cout << "You escape" << endl;
				break;
			}
			Effect first;
			Effect second;
			if (sortSequence(player1Effect, player2Effect)) {
				first = player1Effect;
				second = player2Effect;
			}
			else {
				first = player2Effect;
				second = player1Effect;
			}
			bool singFlag = true;
			execute(first, field, singFlag);
			loadScene(field);
			execute(second, field, singFlag);
			loadScene(field);

			if (!field->getSlimes().first->isAlive()) {
				field->getSlimes().first->printPlayer();
				cout << field->getSlimes().first->getName() << " is beaten" << endl;
			}
			if (!field->getSlimes().second->isAlive()) {
				field->getSlimes().second->printPlayer();
				cout << field->getSlimes().second->getName() << " is beaten" << endl;
			}

			if (checkEnd(player1, player2, field)) {
				break;
			}

			if (!field->getSlimes().first->isAlive()) {
				player1->changeSlime(field);
				cout << endl;
			}
			if (!field->getSlimes().second->isAlive()) {
				player2->changeSlime(field);
				cout << endl;
			}
			loadScene(field);

			field->printHealth();
			cout << "--------------------------------------------------\n";
		}
	}
}