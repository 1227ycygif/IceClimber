# 🎮 IceClimber
아이스클라이머 / C++ 모작 프로젝트 

## 📌 프로젝트 정보 
- **개발 기간 :** 3주 
- **팀 구성 :** 3명 
- **개발 환경 :** Visual Studio, C++, DirectX 9, MySQL 5.7 

## 📋 역할 분담 및 기여도 

### 🎯 본인 주요 담당 (설계 + 구현 주도) 
✅ **인터렉션 블록 시스템** (단독) 
- 'Block.cpp/h' - 블록 물리, 파괴 효과 
- ※ 블록 - 플레이어 충돌, 파괴 물리, 몬스터 인식 로직 부분 단독, 나머지 공동 협업 
- 'BlockManager.cpp/h' - 블록 생성 및 관리 
- 'Collider.cpp/h' - AABB 충돌 처리 유틸리티 

✅ **DB 연결 설정** (단독) 
- 'Define.h'(DB_HOST, DB_USER, DB_PASS, DB_NAME 부분) 

✅ **MySQL 랭킹 시스템** (단독) 
- 'mysql.cpp/h' - 데이터베이스 연결, 저장, 조회 
- 'Data.cpp/h' - 플레이어 점수 데이터 구조체 

### 🤝 팀 협업 파일 (공동 설계 및 구현) 
**게임 로직 연동** 
- 'MapManager.cpp/h' - 맵-블록 통합 관리 
- 'Monster.cpp/h' - 몬스터 AI (블록 인식 부분 협업) 
- 'Menu.cpp' - 랭킹 UI 렌더링 (DB 연동 부분) 
- 'Over.cpp' - 점수 계산 및 저장 
- 'Define.h' - 맵 구성 배열 (공동) 

### 📚 수업 제공 기본 프레임워크 
DirectX 9 기반 게임 엔진 구조 (선생님 제공) 
- `Device.cpp/h`, `DeviceFont.cpp/h` - DirectX 초기화 및 폰트 
- `DXUTsound.cpp/h`, `Sprite.cpp/h` - 사운드/스프라이트 렌더링 
- `Chap.h`, `CMng.cpp/h` - 씬 관리 구조 
- `Main.cpp` - 메인 루프 및 진입점 
- `Include.h` - 공통 헤더 (사용자 추가 파일 부분은 공동 협업) 

### 👥 팀원 주도 파일
- 'Character.cpp/h' - 캐릭터 시스템
- 'Map.cpp/h' - 맵 렌더링
- 'GameManager.cpp/h' - 게임 상태 관리
- 'Logo.cpp/h', 'Game.cpp/h' - 씬 구현
- 'Sound.cpp/h' - 사운드 관리

## ⚙️ 개발 방식 
- 45개 스크립트를 3명이 3주간 협업
- 핵심 시스템별로 담당자를 정하되 연동 부분은 함께 작업
- 회의를 통해 충돌 처리 및 데이터 흐름 조절
- 기본 베이스가 되는 수업 자료(D3D) 기반 파일 존재 

## 🔧 기술 스택 
- **언어 :** C++ 
- **그래픽 :** DIrectX 9 
- **데이터베이스 :** MySQL 5.7 
- **DB 연동 :** MySQL C API(libmysql)

## 💾 데이터베이스 설계 
```sql
CREATE TABLE rank(
first VARCHAR(10), middle VARCHAR(10), last VARCHAR(10),
score INT(11),
first2 VARCHAR(10), middle2 VARCHAR(10), last2 VARCHAR(10),
score INT(11)
);
```

## ⚠️ 주의사항 
- DB 비밀번호는 보안상 제거되었습니다
- 로컬 실행 시 'Define.h'에서 비밀번호를 입력하세요

## 상세 내용 
더 자세한 포트폴리오는 다음 링크에서 확인하실 수 있습니다 
