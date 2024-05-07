FROM leo3-build AS builder

FROM adoptopenjdk/openjdk11:jre-11.0.9_11.1-alpine
#FROM adoptopenjdk/openjdk11:jre-11.0.6_10-alpine

COPY --from=builder /artifacts/leo* /usr/bin/

ENTRYPOINT ["leo3"]
