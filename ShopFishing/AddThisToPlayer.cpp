float Player::getMoney() const { 
    return money; 
}

void Player::addMoney(float amount) { 
    money += amount; 
    std::cout << "Gained $" << amount << ". Total: $" << money << std::endl;
}

void Player::spendMoney(float amount) { 
    money -= amount; 
    std::cout << "Spent $" << amount << ". Remaining: $" << money << std::endl;
}

void Player::addRod(std::shared_ptr<FishingRod> rod) { 
    obtained_rods.push_back(rod); 
}

bool Player::ownsRod(std::shared_ptr<FishingRod> rod) const {
    for (const auto& owned_rod : obtained_rods) {
        if (owned_rod == rod) return true;
    }
    return false;
}