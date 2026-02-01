# QA Issue Report (2026-02-01)

## 요약
- 수정된 이슈 4
- 남은 이슈 1
- 판단 요약 P1 성능 이슈 포함 4건 해결, SpawnPoint 부재 크래시 가능 이슈 1건 잔존

## 수정 내역

### Issue #1 시작 시 플레이어 HP UI가 0으로 표시됨
- 우선순위 P2
- 수정 내용 시작 시 HP UI가 정상 표시되도록 초기 표시 로직 보정 (상세 수정 내용 미기재)
- 검증 방법 PIE 실행 후 HP UI 정상 표시 확인

### Issue #2 적 발사 패턴이 종료되지 않고 반복 실행되는 문제
- 우선순위 P2
- 수정 내용 `CurrentBurstCount` 초기화 0으로 수정, `TryStartFiring`에서 `bHasFired` 검사 추가
- 검증 방법 PIE 실행 후 발사 패턴 정상 표시 확인

### Issue #4 적 총알 수명이 적용되지 않아 장시간 잔존
- 우선순위 P3
- 수정 내용 `SetActive(true)` 시 LifeTime 타이머 시작, `OnLifeTimeExpired()`에서 `Destroy()` 호출 추가
- 검증 방법 ActorTracking.log로 BP_EnemyBullet_C 개수 안정화 확인 (12~21)

### Issue #5 SpawnFrequency 비정상 설정으로 성능 저하
- 우선순위 P1
- 수정 내용 ClampMin="0.1" 추가, BeginPlay 런타임 검증/경고 로그 추가, MaxActiveEnemies 상한 설정
- 검증 방법 게임 플레이로 FPS 88.5 확인, ClampMin 작동 검증

## 남은 이슈

### Issue #3 SpawnPoint가 없으면 적 스폰 시 크래시 가능
- 관리 대상 사유 QA_Issues.md에 해결 상태 미기재(미해결)

## 참고 자료
- 관련 로그 파일 ActorTracking.log (경로 미기재)
- 트레이스 파일 Unreal Insights 트레이스 (경로 미기재), TimerStats.csv (경로 미기재)
