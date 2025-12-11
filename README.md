# IceClimber
아이스클라이머 / C++ 모작 프로젝트

## 프로젝트 정보 
- **개발 기간 :** 3주
- **팀 구성 :** 3명 
- **개발 환경 :** Visual Studio, C++, DirectX 9, MySQL 5.7

## 담당 파트 
- **인터렉션 블록 시스템 :** 블록 파괴, 블록 충돌 처리
- **UI 시스템 :** 이름 입력, 랭킹 표시
- **MySQL 랭킹 시스템 :** DB 연동, 점수 저장/조회

## 담당 파일 
**100% 작업** 
- 'mysql.cpp', 'mysql.h' - MySQL 데이터베이스 연동

**일부 작업**
- 'Menu.cpp' : 랭킹 UI 부분 
- 'Over.cpp' : 점수 계산 및 저장 부분

## 기술 스택 
- **언어 :** C++ 
- **그래픽 :** DIrectX 9 
- **데이터베이스 :** MySQL 5.7 
- **DB 연동 :** MySQL C API(libmysql)

## 데이터베이스 설계 
```sql
CREATE TABLE rank(
first VARCHAR(10), middle VARCHAR(10), last VARCHAR(10),
score INT(11),
first2 VARCHAR(10), middle2 VARCHAR(10), last2 VARCHAR(10),
score INT(11)
);
```

## 주의사항 
- DB 비밀번호는 보안상 제거되었습니다
- 로컬 실행 시 'Define.h'에서 비밀번호를 입력하세요

## 상세 내용 
더 자세한 포트폴리오는 다음 링크에서 확인하실 수 있습니다 
