#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Drink {
public:
    string name;
    int volume;
    int price; // new price variable

    Drink(string n, int v, int p) : name(n), volume(v), price(p) {}
    virtual ~Drink() {}
};

class AlcoholicDrink : public Drink {
public:
    int alcoholContent;
    string color;
    string type;
    string taste;
    string origin;

    AlcoholicDrink(string n, int v, int p, int ac, string c, string t, string o, string ta)
        : Drink(n, v, p), alcoholContent(ac), color(c), type(t), taste(ta), origin(o) {}
};

class NonAlcoholicDrink : public Drink {
public:
    string taste;
    int sugarContent;
    string color;
    string type;
    bool carbonated;
    string consistency;

    NonAlcoholicDrink(string n, int v, int p, string t, int sc, string c, bool ga, string co)
        : Drink(n, v, p), taste(t), sugarContent(sc), color(c), carbonated(ga), consistency(co) {}
};

class HotDrink : public Drink {
public:
    string aroma;
    int temperature;
    string taste;
    string composition;

    HotDrink(string n, int v, int p, string a, int temp, string t, string c)
        : Drink(n, v, p), aroma(a), temperature(temp), taste(t), composition(c) {}
};

class Bar {
private:
    vector<Drink*> drinks;

public:
    void searchDrinkByName(const string& drinkName) {
        for (int i = 0; i < drinks.size(); i++) {
            if (drinks[i]->name == drinkName) {
                cout << "Найден напиток:" << endl;
                cout << "Название: " << drinks[i]->name << endl;
                cout << "Объем: " << drinks[i]->volume << " мл" << endl;
                cout << "Цена: " << drinks[i]->price << " руб." << endl;
                return;
            }
        }
        cout << "Напиток с названием '" << drinkName << "' не найден." << endl;
    }

    void displayDetailedInfo(int index) {
        cout << "Информация о напитке:" << endl;
        cout << "Название: " << drinks[index]->name << endl;
        cout << "Объем: " << drinks[index]->volume << " мл" << endl;
        cout << "Цена: " << drinks[index]->price << " руб." << endl;
        if (AlcoholicDrink* alcDrink = dynamic_cast<AlcoholicDrink*>(drinks[index])) {
            cout << "Алкогольный: Да" << endl;
            cout << "Содержание алкоголя: " << alcDrink->alcoholContent << "%" << endl;
        }
        else if (NonAlcoholicDrink* nonAlcDrink = dynamic_cast<NonAlcoholicDrink*>(drinks[index])) {
            cout << "Алкогольный: Нет" << endl;
            cout << "Сахар: " << nonAlcDrink->sugarContent << " г" << endl;
            cout << "Газированный: " << (nonAlcDrink->carbonated ? "Да" : "Нет") << endl;
        }
        else if (HotDrink* hotDrink = dynamic_cast<HotDrink*>(drinks[index])) {
            cout << "Алкогольный: Нет" << endl;
            cout << "Аромат: " << hotDrink->aroma << endl;
            cout << "Температура: " << hotDrink->temperature << " градусов Цельсия" << endl;
            cout << "Состав: " << hotDrink->composition << endl;
        }
    }

    void addDrink(Drink* d) {
        drinks.push_back(d);
    }

    void removeDrink(int index) {
        drinks.erase(drinks.begin() + index);
    }

    void editDrink(int index, Drink* newDrink) {
        drinks[index] = newDrink;
    }

    void viewDrinks() {
        for (int i = 0; i < drinks.size(); i++) {
            cout << i + 1 << ". " << drinks[i]->name << ", " << drinks[i]->volume << " мл, " << drinks[i]->price << " руб." << endl;
        }
    }

    int placeOrder() {
        int orderTotal = 0;
        cout << "Введите номер напитка, который хотите заказать (0 для завершения заказа): ";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 0) {
                break;
            }
            if (choice > 0 && choice <= drinks.size()) {
                orderTotal += drinks[choice - 1]->price; // use price instead of volume
                cout << "Напиток добавлен в заказ. Общая стоимость заказа: " << orderTotal << " руб." << endl;
            }
            else {
                cout << "Неверный номер напитка. Попробуйте еще раз." << endl;
            }
            cout << "Введите номер напитка, который хотите заказать (0 для завершения заказа): ";
        }
        return orderTotal;
    }

    int calculateCost(int orderTotal) {
        return orderTotal;
    }

    void receivePayment(int cost) {
        int payment;
        cout << "Введите сумму платежа: ";
        cin >> payment;
        if (payment >= cost) {
            int change = payment - cost;
            cout << "Сдача: " << change << " руб." << endl;
        }
        else {
            cout << "Недостаточно средств. Попробуйте еще раз." << endl;
            receivePayment(cost);
        }
    }


};

int main() {
    setlocale(LC_ALL, "Rus");
    Bar bar;

    bar.addDrink(new AlcoholicDrink("Vodka", 500, 400, 40, "Белый", "Водка", "Классический", "Россия"));
    bar.addDrink(new NonAlcoholicDrink("Kola", 330, 150, "Сладкий", 110, "Коричневый", true, "Газированная"));
    bar.addDrink(new HotDrink("Coffee", 200, 250, "Ароматный", 85, "Горький", "Кофеин, вода"));

    while (true) {
        cout << "Выберите действие:\n"
            << "1. Просмотр напитков\n"
            << "2. Заказ напитков\n"
            << "3. Добавить новый напиток\n"
            << "4. Изменить напиток\n"
            << "5. Удалить напиток\n"
            << "6. Найти напиток по названию\n"
            << "7. Отобразить детальную информацию напитка\n"
            << "Ваш выбор: ";

        int choice;
        cin >> choice;


        if (choice == 1) {
            bar.viewDrinks();
        }
        else if (choice == 2) {
            int orderTotal = bar.placeOrder();
            if (orderTotal > 0) {
                int cost = bar.calculateCost(orderTotal);
                bar.receivePayment(cost);
            }
        }
        else if (choice == 3) {
            cout << "Введите тип напитка 1. Алкогольный напиток 2. Безалкогольный напиток 3. Горячий напиток\n";
            int typedrink;
            cin >> typedrink;
            if (typedrink == 1) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Градус в %:\n"; int gradusnewdrink; cin >> gradusnewdrink;
                cout << "Цвет:\n"; string colornewdrink; cin >> colornewdrink;
                cout << "Тип:\n"; string typenewdrink; cin >> typenewdrink;
                cout << "Страна:\n"; string countrynewdrink; cin >> countrynewdrink;
                bar.addDrink(new AlcoholicDrink(namenewdrink, volumenewdrink, pricenewdrink, gradusnewdrink, colornewdrink, typenewdrink, "Классический", countrynewdrink));
            }
            else if (typedrink == 2) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Аромат:\n"; string aromanewdrink; cin >> aromanewdrink;
                cout << "Температура\n"; int tempnewdrink; cin >> tempnewdrink;
                cout << "Цвет:\n"; string colornewdrink; cin >> colornewdrink; bool gazdrink;
                cout << "1. Газированная, 2. Негазированная\n"; int gaznewdrink; cin >> gaznewdrink; if (gaznewdrink == 1) {
                    gazdrink = true;
                }
                else if (gaznewdrink == 2) {
                    gazdrink = false;
                }
                cout << "Консистенция:\n"; string consnewdrink; cin >> consnewdrink;
                bar.addDrink(new NonAlcoholicDrink(namenewdrink, volumenewdrink, pricenewdrink, aromanewdrink, tempnewdrink, colornewdrink, gazdrink, consnewdrink));
            }
            else if (typedrink == 3) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Аромат:\n"; string aromanewdrink; cin >> aromanewdrink;
                cout << "Температура:\n"; int tempnewdrink; cin >> tempnewdrink;
                cout << "Вкус:\n"; string vkusnewdrink; cin >> vkusnewdrink;
                cout << "Состав:\n"; string sostavnewdrink; cin >> sostavnewdrink;
                bar.addDrink(new HotDrink(namenewdrink, volumenewdrink, pricenewdrink, aromanewdrink, tempnewdrink, vkusnewdrink, sostavnewdrink));
            }
        }
        else if (choice == 4) {
            cout << "Введите номер изменяемого напитка:\n"; int index; cin >> index;
            cout << "Введите тип напитка 1. Алкогольный напиток 2. Безалкогольный напиток 3. Горячий напиток\n";
            int typedrink;
            cin >> typedrink;
            if (typedrink == 1) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Градус в %:\n"; int gradusnewdrink; cin >> gradusnewdrink;
                cout << "Цвет:\n"; string colornewdrink; cin >> colornewdrink;
                cout << "Тип:\n"; string typenewdrink; cin >> typenewdrink;
                cout << "Страна:\n"; string countrynewdrink; cin >> countrynewdrink;
                bar.editDrink(index+1, new AlcoholicDrink(namenewdrink, volumenewdrink, pricenewdrink, gradusnewdrink, colornewdrink, typenewdrink, "Классический", countrynewdrink));
            }
            else if (typedrink == 2) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Аромат:\n"; string aromanewdrink; cin >> aromanewdrink;
                cout << "Температура\n"; int tempnewdrink; cin >> tempnewdrink;
                cout << "Цвет:\n"; string colornewdrink; cin >> colornewdrink; bool gazdrink;
                cout << "1. Газированная, 2. Негазированная\n"; int gaznewdrink; cin >> gaznewdrink; if (gaznewdrink == 1) {
                    gazdrink = true;
                }
                else if (gaznewdrink == 2) {
                    gazdrink = false;
                }
                cout << "Консистенция:\n"; string consnewdrink; cin >> consnewdrink;
                bar.editDrink(index, new NonAlcoholicDrink(namenewdrink, volumenewdrink, pricenewdrink, aromanewdrink, tempnewdrink, colornewdrink, gazdrink, consnewdrink));
            }
            else if (typedrink == 3) {
                cout << "Название напитка:\n"; string namenewdrink; cin >> namenewdrink;
                cout << "Объем:\n"; int volumenewdrink; cin >> volumenewdrink;
                cout << "Цена в руб.:\n"; int pricenewdrink; cin >> pricenewdrink;
                cout << "Аромат:\n"; string aromanewdrink; cin >> aromanewdrink;
                cout << "Температура:\n"; int tempnewdrink; cin >> tempnewdrink;
                cout << "Вкус:\n"; string vkusnewdrink; cin >> vkusnewdrink;
                cout << "Состав:\n"; string sostavnewdrink; cin >> sostavnewdrink;
                bar.editDrink(index, new HotDrink(namenewdrink, volumenewdrink, pricenewdrink, aromanewdrink, tempnewdrink, vkusnewdrink, sostavnewdrink));
            }
        }
        else if (choice == 5) {
            cout << "Введите номер удаляемого напитка:\n"; int index; cin >> index;
            bar.removeDrink(index);
        }
        else if (choice == 6) {
            cout << "Введите название напитка:\n"; string namedrink; cin >> namedrink;
            bar.searchDrinkByName(namedrink);
        }
        else if (choice == 7) {
            cout << "Введите номер напитка: "; int index; cin >> index;
            bar.displayDetailedInfo(index-1);
        }
        else {
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    }
    return 0;
}