# Контекст решения
<!-- Окружение системы (роли, участники, внешние системы) и связи системы с ним. Диаграмма контекста C4 и текстовое описание. 
-->
```plantuml
@startuml cont
skinparam defaultFontName Helvetica
skinparam roundcorner 20
left to right direction
skinparam shadowing<<System>> true

!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

Person(admin, "Администратор") #Teal
Person(moderator, "Модератор") #Teal
Person(user, "Пользователь") #Teal

System(socialnet, "ВМесте", "Веб-сайт социальной сети с личной страницей пользователя и P2P мессенджером") #LightSeaGreen/TECHNOLOGY


Rel(admin, socialnet, "Просмотр, добавление и редактирование информации о пользователях, записях на стене и P2P сообщениях")
Rel(moderator, socialnet, "Модерация контента и пользователей")
Rel(user, socialnet, "Регистрация и поиск пользователей, просмотр и отправка сообщений, просмотр и изменение стены")

@enduml
```
## Назначение систем
|Система| Описание|
|-------|---------|
| Сайт социальной сети | Веб-интерфейс, обеспечивающий доступ к информации о стене пользователя и внутреннем Р2Р мессенджере. Бэкенд сервиса реализован в виде микросервисной архитектуры |
