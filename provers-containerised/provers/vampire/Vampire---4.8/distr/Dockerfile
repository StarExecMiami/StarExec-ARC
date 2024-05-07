FROM vampire-build AS builder

FROM bitnami/minideb

COPY --from=builder /artifacts/vampire* /usr/bin/vampire

ENTRYPOINT ["vampire"]
