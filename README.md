# DND_RogueLike

## Авторы
1. [Шейко Михаил](https://gitlab.akhcheck.ru/sheiko.mikhail)
2. [Макар Расанов](https://gitlab.akhcheck.ru/makar.rasanov)
3. [Мелеховец Кирилл](https://gitlab.akhcheck.ru/kirill.melekhovets)

## Сборка проекта
Чтобы скопировать и запустить проект воспользуйтесь следующими командами:
```shell
git clone -b checkpoint_1 --recurse-submodules -j8 git@gitlab.akhcheck.ru:sheiko.mikhail/tp_course_spring24_project.git
cd tp_course_spring24_project
mkdir build
cd build
cmake ..
make
```

## Описание архитектуры проекта
В [assets](https://gitlab.akhcheck.ru/sheiko.mikhail/tp_course_spring24_project/-/tree/checkpoint_1/assets?ref_type=heads) находятся ресурсы игры.

В [rooms](https://gitlab.akhcheck.ru/sheiko.mikhail/tp_course_spring24_project/-/tree/checkpoint_1/rooms?ref_type=heads) находятся сохранённые комнаты.

**CBaseAnimation** содержит в себе информацию об анимациию (кол-во кадров, длительность кадра и т.д.).

**CAssetsManager** содержит в себе указатели на подгруженные ресурсы.

**IBaseEventListener** - интерфейс, которому должны удовлетворять все объекты типа EventListener.

**IBaseEntity** - интерфейс, который содержит информацию о сущностях.

**CEntityList** - хранит множество сущностей.

**CEntityNode** - хранит родителя и детей сущности.

**CBaseEquipment** - хранит характеристики эквипа.

**CBaseWeapon** - хранит характеристики (обычного) оружия.

**CRangedWeapon** - хранит характеристики оружия дальнего боя.

**CBaseArmor** - хранит характеристики брони.

**CBasePotion** - хранит характеристики зелий.

**CEventListenerNode** - жлемент двусвязного списка, хранящий EventListener.

**CSpecificEventManager** - шаблонный обработчик ивентов.

**CEventManager** - обрабатывает все ивенты через из обработчиков.

**CTileHoverEventListener** - отдельный обработчик наведения на CTile.

**CTileClickEventListener** - отдельный обработчки клика на CTile.

**IBaseMouseEventListener** - общий обработчик ивентов, связанных с мышью.

**CBasePlayer** содержит в себе общую информацию об игроке.

**CBaseMonster** содержит в себе общую информацию о монстре.

**CTile** хранит характеристики клеток, из которых состоит поле.

**Room** хранит характеристики поля(в том числе вектор CTile).