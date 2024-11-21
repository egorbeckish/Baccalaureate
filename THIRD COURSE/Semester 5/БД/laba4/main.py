import psycopg2

originall = {
    'dbname': 'tusur',
    'user': 'postgres',
    'password': '123',
}

connect = psycopg2.connect(**originall)
cursor = connect.cursor()
connect.autocommit = True

query = """
insert into room (rnum, tnum)
values
('000', '000000'),
('001', '000001'),
('002', '000002'),
('003', '000003')
;


insert into student (snum, snam, ann, stel, rnum)
values
('000000', 'Баранов Алексей Андреевич', '1', '9130000000', '000'),
('000001', 'Барашкин Алексей Андреевич', '1', '9130000001', '000'),
('000002', 'Быков Алексей Андреевич', '1', '9130000002', '000'),
('000003', 'Воловский Алексей Андреевич', '2', '9130000003', '001'),
('000004', 'Гатов Николай Саввич', '3', '9130000004', '002'),
('000005', 'Батов Иван Константинович', '4', '9130000005', '003')
;

insert into "pr-dis" (pnam, dnam)
values
('Белоусова София Романовна', 'ПЯВУ'),
('Морозова Майя Андреевна', 'ВУПЯ'),
('Медведев Лев Юрьевич', 'Теоритические основы куроедения'),
('Попов Михаил Кириллович', 'Меланжевое производство'),
('Кулаков Роман Родионович', 'Технология собаковыгуливания'),
('Мальцев Матвей Ильич', 'Технология приготовления яичницы')
;

insert into exams (snum, sem, pnam, ball)
values
('000000', '1', 'Белоусова София Романовна', '4'),
('000000', '1', 'Морозова Майя Андреевна', '4'),
('000000', '1', 'Медведев Лев Юрьевич', '4'),

('000001', '1', 'Белоусова София Романовна', '4'),
('000001', '2', 'Морозова Майя Андреевна', '3'),

('000002', '1', 'Морозова Майя Андреевна', '5'),
('000002', '1', 'Медведев Лев Юрьевич', '3'),
('000002', '1', 'Попов Михаил Кириллович', '4'),

('000003', '1', 'Белоусова София Романовна', '3'),
('000003', '2', 'Медведев Лев Юрьевич', '5'),
('000003', '3', 'Кулаков Роман Родионович', '3'),
('000003', '4', 'Морозова Майя Андреевна', '4'),

('000004', '3', 'Белоусова София Романовна', '5'),
('000004', '3', 'Медведев Лев Юрьевич', '5'),
('000004', '3', 'Попов Михаил Кириллович', '5'),

('000005', '1', 'Белоусова София Романовна', '4'),
('000005', '2', 'Морозова Майя Андреевна', '3'),
('000005', '3', 'Кулаков Роман Родионович', '5'),
('000005', '4', 'Попов Михаил Кириллович', '3'),
('000005', '5', 'Медведев Лев Юрьевич', '5'),
('000005', '6', 'Мальцев Матвей Ильич', '3')
;"""

cursor.execute(query)


def foo(snum):
    query = '''select * from "pr-dis";'''
    cursor.execute(query)
    pr_dis = cursor.fetchall()
    pr_dis_dict = {pr_dis[i][0]: pr_dis[i][1] for i in range(len(pr_dis))}

    query = f'''select sem, pnam, ball from exams where snum='{snum}';'''
    cursor.execute(query)
    exams = cursor.fetchall()

    query = f'''select avg(ball) from exams where snum='{snum}';'''
    cursor.execute(query)
    middle = str(cursor.fetchone()[0])

    if middle[2:4] == '00':
        middle = int(middle[:middle.index('.')])
    elif middle[3] == '0' or middle[3] != '5':
        middle = middle[:3]
    else:
        middle = middle[:4]

    s = 'Дисциплина\t\t\t\t\t\tОценка\tСеместр\n'
    for info in exams:
        sem, pnam, ball = info
        s += f'\t\t\t\t\t\t\t\t\t {pr_dis_dict[pnam]:35}{ball}{sem:10}\n'
    s += f'\t\t\t\t\t\t\t\t\t\t\t   {"Средний балл":25}{middle}'
    return s


query = '''select ann from student;'''
cursor.execute(query)
ann = set(cursor.fetchall())

for year in ann:
    query = f'''select snum, snam from student where ann={year[0]}'''
    cursor.execute(query)
    student_info = cursor.fetchall()
    print(f'Год обучения:{year[0]}')
    for info in student_info:
        snum, snam = info
        print(f'{snam}\t\t\t{foo(snum)}\n')

query = """
delete from exams;
delete from student;
delete from room;
delete from "pr-dis";
"""

cursor.execute(query)

cursor.close()
connect.close()
